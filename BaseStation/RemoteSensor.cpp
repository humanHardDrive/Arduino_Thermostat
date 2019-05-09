#include "RemoteSensor.h"

#include <string.h>

RemoteSensor::RemoteSensor()
{
	memset(m_SavedData.networkID, 0, 8);
	m_SavedData.devID = 0;
}

RemoteSensor::~RemoteSensor()
{
}

void RemoteSensor::background()
{
	uint8_t buffer[128];
	uint16_t size;
	
	if(available())
	{
		size = read(buffer, sizeof(buffer));
		handleMessage(buffer, size);
	}
	
	if(m_bInDiscovery)
	{
		if((clockms() - m_nPairStartTime) > m_nDiscoveryTimeout)
			m_bInDiscovery = false;
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
	m_nDiscoveryRspDelay = 5;
	m_nDiscoveryTimeout = timeout;
}

void RemoteSensor::buildPacket(uint8_t msgType, uint8_t src, uint8_t dst, uint8_t* payload, uint16_t len, uint8_t* outBuf, uint16_t* outLen)
{
	*(outBuf + MSG_DST) = dst;
	*(outBuf + MSG_SRC) = src;
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
	switch(cmd)
	{
		case REMOTE_INIT_MSG:
		break;
		
		case REMOTE_DESC_MSG:
		break;
		
		case PASSTHROUGH_MSG:
		break;
		
		case REMOTE_DISC_MSG:
		discoveryHandler(buffer, len);
		break;
		
		case REMOTE_DISC_ACK:
		break;
	}
}

void RemoteSensor::handleMessage(const void* buffer, uint16_t len)
{
	uint8_t dst = *((uint8_t*)(buffer + MSG_DST));
	
	if(dst == m_SavedData.devID)
	{
		uint8_t cmd = *((uint8_t*)(buffer + MSG_TYPE));
		uint16_t size;
		memcpy(buffer + MSG_LEN, &size, 2);
		
		handleCommand(cmd, buffer + MSG_PAYLOAD, size);
	}
}

void RemoteSensor::discoveryHandler(const void* buffer, uint16_t len)
{
	uint8_t rspBuf[16];
	uint16_t rspLen;
	
	
	print(__PRETTY_FUNCTION__);
	
	buildPacket((uint8_t)(REMOTE_DISC_ACK), (uint8_t)0, (uint8_t)0, NULL, (uint16_t)0, rspBuf, &rspLen);
	write(rspBuf, rspLen);
}

void RemoteSensor::discoveryAckHandler(const void* buffer, uint16_t len)
{
}