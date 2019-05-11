#include "BaseStation.h"
#include "CommBase.h"

#include <string.h>

BaseStation::BaseStation()
{
	m_bInDiscovery = false;
	m_nMsgID = 0;
}

BaseStation::~BaseStation()
{
}

void BaseStation::startDiscovery(uint32_t timeout)
{
	print(__PRETTY_FUNCTION__);
	
	m_nDiscoveryTimeout = timeout;
	m_nDiscoveryStartTime = clockms();
	m_nRemoteDiscovered = 0;
	m_nLastDiscoveryPollTime = 0;
	
	memset(m_DiscoveredDevice, 0, sizeof(m_DiscoveredDevice));
	
	m_bInDiscovery = true;
}

uint8_t BaseStation::getDiscoveryCount()
{
	return m_nRemoteDiscovered;
}

void BaseStation::background()
{
	if(m_bInDiscovery)
		discovery();
	
	if(available())
	{
		uint8_t rspBuffer[16];
		uint16_t rspLen;
		
		rspLen = read(rspBuffer, 16);
		handleMessage(rspBuffer, rspLen);
	}
}

void BaseStation::discovery()
{
	if((m_nLastDiscoveryPollTime + 300) < clockms())
	{
		uint8_t DiscoverMsg[16];
		uint16_t MsgSize;
		
		buildPacket((uint8_t)(REMOTE_DISC_MSG), &m_nMsgID, (uint32_t)0, (uint32_t)0, NULL, (uint16_t)0, DiscoverMsg, &MsgSize);
		
		write(DiscoverMsg, MsgSize);
		m_nLastDiscoveryPollTime = clockms();
	}
	
	if((m_nDiscoveryStartTime + m_nDiscoveryTimeout) < clockms())
	{
		m_bInDiscovery = false;
		stopDiscovery();
	}
}

void BaseStation::handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len)
{
	if(m_bInDiscovery)
	{
		switch(cmd)
		{		
			case REMOTE_DISC_MSG:
			break;
			
			case REMOTE_DISC_ACK:
			discoveryAckHandler(src, buffer, len);
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

void BaseStation::handleMessage(const void* buffer, uint16_t len)
{
	uint32_t dst = *((uint32_t*)(buffer + MSG_DST));
	uint32_t src = *((uint32_t*)(buffer + MSG_SRC));
	
	if(!dst)
	{
		uint8_t cmd = *((uint8_t*)(buffer + MSG_TYPE));
		uint16_t size;
		memcpy(buffer + MSG_LEN, &size, 2);
		
		handleCommand(cmd, src, buffer + MSG_PAYLOAD, size);
	}
}

void BaseStation::discoveryAckHandler(uint32_t src, const void* buffer, uint16_t len)
{
	print(__PRETTY_FUNCTION__);
	
	addDiscoveredDevice(src, (char*)(buffer));
}

uint8_t BaseStation::addDiscoveredDevice(uint32_t UID, char* name)
{
	uint8_t emptyIndex = 0xFF;
	
	print(__PRETTY_FUNCTION__);
	
	for(uint8_t i = 0; i < 16; i++)
	{
		if(m_DiscoveredDevice[i].UID == UID)
		{
			print("ALREADY PRESENT");
			return 1;
		}
		
		if(emptyIndex == 0xFF && !m_DiscoveredDevice[i].UID)
			emptyIndex = i;
	}
	
	if(emptyIndex == 0xFF)
	{
		print("NO ROOM");
		return 2;
	}
	
	m_DiscoveredDevice[emptyIndex].UID = UID;
	memcpy(m_DiscoveredDevice[emptyIndex].name, name, 16);
	m_nRemoteDiscovered++;
	
	print("ADDED DEVICE");
	
	return 0;
}