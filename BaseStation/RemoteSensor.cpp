#include "RemoteSensor.h"

#include <string.h>

RemoteSensor::RemoteSensor()
{
	memset(m_SavedData.networkID, 0, 8);
	memset(m_SavedData.name, 0, 16);
	m_SavedData.UID = 0x11223344; //Temporary
	strcpy(m_SavedData.name, "SENSOR");
	
	m_nMsgID = 0;
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
		buildPacket((uint8_t)(REMOTE_DISC_ACK), &m_nMsgID, m_SavedData.UID, (uint8_t)0,
					(uint8_t*)&m_SavedData.name, (uint16_t)REMOTE_NAME_LENGTH, rspBuf, &rspLen);
		write(rspBuf, rspLen);
		m_nDiscoveryMsgTime = 0;
	}
}

void RemoteSensor::forget()
{
	print(__PRETTY_FUNCTION__);
	
	memset(m_SavedData.networkID, 0, 8);
}

void RemoteSensor::pair(uint16_t timeout)
{
	print(__PRETTY_FUNCTION__);
	
	m_bInDiscovery = true;
	m_nPairStartTime = clockms();
	m_nDiscoveryMsgTime = 0;
	m_nDiscoveryTimeout = timeout;
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
			
			case REMOTE_INIT_MSG:
			deviceInitHandler(buffer, len);
			break;
		}
	}
	else
	{
		switch(cmd)
		{			
			case REMOTE_DESC_MSG:
			break;
			
			case PASSTHROUGH_MSG:
			break;
			
			//Handle the message here in case the base station doesn't hear the response
			//And it will try again
			case REMOTE_INIT_MSG:
			deviceInitHandler(buffer, len);
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

void RemoteSensor::deviceInitHandler(const void* buffer, uint16_t len)
{
	print(__PRETTY_FUNCTION__);
	
	INIT_MSG msg;
	memcpy(&msg, buffer, sizeof(INIT_MSG));
	
	if(msg.UID == m_SavedData.UID)
	{
		memcpy(m_SavedData.networkID, msg.networkID, NETWORK_LEGNTH);
		m_bInDiscovery = false;
	}
}