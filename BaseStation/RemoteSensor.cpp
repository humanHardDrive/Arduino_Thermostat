#include "RemoteSensor.h"

#include <string.h>

RemoteSensor::RemoteSensor()
{
	memset(m_SavedData.networkID, 0, 8);
	m_SavedData.UID = 0x11223344; //Temporary
}

RemoteSensor::~RemoteSensor()
{
}

void RemoteSensor::background()
{
	uint8_t buffer[128];
	uint16_t size;
	
	if(m_bInDiscovery)
		discoveryBackground();
	
	if(available())
	{
		size = read(buffer, sizeof(buffer));
		handleMessage(buffer, size);
	}
}

void RemoteSensor::discoveryBackground()
{
	uint8_t rspBuf[16];
	uint16_t rspLen;
	
	if(m_nDiscoveryMsgTime && (m_nDiscoveryMsgTime + m_nDiscoveryRspDelay) < clockms())
	{
		print("Disc rsp");
		buildPacket((uint8_t)(REMOTE_DISC_ACK), (uint8_t)0, (uint8_t)0, (uint8_t*)&m_SavedData.devID, (uint16_t)1, rspBuf, &rspLen);
		write(rspBuf, rspLen);
		m_nDiscoveryMsgTime = 0;
	}
}

void RemoteSensor::forget()
{
	print(__PRETTY_FUNCTION__);
	
	memset(m_SavedData.networkID, 0, 8);
	m_SavedData.devID = 0;
}

void RemoteSensor::pair(uint16_t timeout)
{
	print(__PRETTY_FUNCTION__);
	
	m_bInDiscovery = true;
	m_nPairStartTime = clockms();
	m_nDiscoveryMsgTime = 0;
	m_nDiscoveryTimeout = timeout;
}

void RemoteSensor::buildPacket(uint8_t msgType, uint32_t src, uint32_t dst, uint8_t* payload, uint16_t len, uint8_t* outBuf, uint16_t* outLen)
{
	memcpy(outBuf + MSG_DST, &dst, 4);
	memcpy(outBuf + MSG_SRC, &src, 4);
	memcpy(outBuf + MSG_ID, &m_nMsgID, 2);
	memcpy(outBuf + MSG_LEN, &len, 2);
	*(outBuf + MSG_TYPE) = msgType;
	
	if(payload)
		memcpy(outBuf + MSG_PAYLOAD, payload, len);
	
	*outLen = len + HEADER_SIZE;
	m_nMsgID++;
}

void RemoteSensor::handleCommand(uint8_t cmd, const void* buffer, uint16_t len)
{
	if(m_bInDiscovery)
	{
		switch(cmd)
		{
			case REMOTE_DISC_MSG:
			discoveryHandler(buffer, len);
			break;
			
			case REMOTE_DISC_ACK:
			discoveryAckHandler(buffer, len);
			break;
		}
	}
	else
	{
		switch(cmd)
		{
			case REMOTE_INIT_MSG:
			break;
			
			case REMOTE_DESC_MSG:
			break;
			
			case PASSTHROUGH_MSG:
			break;
		}
	}
}

void RemoteSensor::handleMessage(const void* buffer, uint16_t len)
{
	uint32_t dst = *((uint32_t*)(buffer + MSG_DST));
	
	if(dst == m_SavedData.UID || m_bInDiscovery)
	{
		uint8_t cmd = *((uint8_t*)(buffer + MSG_TYPE));
		uint16_t size;
		memcpy(buffer + MSG_LEN, &size, 2);
		
		handleCommand(cmd, buffer + MSG_PAYLOAD, size);
	}
}

void RemoteSensor::discoveryHandler(const void* buffer, uint16_t len)
{	
	print(__PRETTY_FUNCTION__);
	
	m_nDiscoveryMsgTime = clockms();
	m_nDiscoveryRspDelay = 5*(rnd()%51); //New random number
}

void RemoteSensor::discoveryAckHandler(const void* buffer, uint16_t len)
{
	print(__PRETTY_FUNCTION__);
	
	m_nDiscoveryMsgTime = clockms();
	m_nDiscoveryRspDelay = 5*(rnd()%51); //New random number
}