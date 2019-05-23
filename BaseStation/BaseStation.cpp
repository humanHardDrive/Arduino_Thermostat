#include "BaseStation.h"
#include "CommBase.h"

#include <string.h>

BaseStation::BaseStation()
{
	m_bInDiscovery = false;
	m_nMsgID = 0;
	
	m_SavedData.UID = 0;
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
	uint8_t rspBuffer[32];
	uint16_t rspLen;
	
	if(m_bInDiscovery)
		discovery();
	
	rspLen = read(rspBuffer, 32);
	if(rspLen)
		handleMessage(rspBuffer, rspLen);
}

bool BaseStation::pair(uint32_t UID, char* sName, uint32_t timeout)
{
	uint8_t buffer[32];
	uint16_t nMsgLen;
	uint32_t nTimeStarted, nRetryTime;
	bool bFound = false;
	INIT_MSG msg;
	
	msg.UID = UID;
	memset(msg.networkID, 0, NETWORK_LEGNTH);
	memcpy(msg.networkID, m_SavedData.networkID, NETWORK_LEGNTH);
	
	nTimeStarted = clockms();
	nRetryTime = 0;
	while((clockms() - nTimeStarted) < timeout && !bFound)
	{
		if((clockms() - nRetryTime) > 15)
		{
			buildPacket((uint8_t)(REMOTE_INIT_MSG), &m_nMsgID, (uint32_t)0, UID, 
						(uint8_t*)&msg, sizeof(INIT_MSG), buffer, &nMsgLen);
			write(buffer, nMsgLen);
			
			nRetryTime = clockms();
		}
		else
		{
			nMsgLen = read(buffer, 32);
			if(nMsgLen && buffer[MSG_TYPE] == REMOTE_INIT_MSG && //Check the message type
			   memcmp(buffer + MSG_SRC, &msg.UID, sizeof(msg.UID)) == 0 && //The source
			   memcmp(buffer + MSG_DST, &m_SavedData.UID, sizeof(m_SavedData.UID)) == 0) //And the destination
			{				
				bFound = true;
				addPairedDevice(UID, sName);
			}
		}
	}
	
	return bFound;
}

bool BaseStation::unpair(uint32_t UID)
{
	for(uint8_t i = 0; i < MAX_PAIRED_COUNT; i++)
	{
		if(m_SavedData.pairedDevice[i].UID == UID)
		{
			m_SavedData.pairedDevice[i].UID = 0;
			memset(m_SavedData.pairedDevice[i].name, 0, REMOTE_NAME_LENGTH);
			return true;
		}
	}
	
	return false;
}

bool BaseStation::isPaired(uint32_t UID)
{
	for(uint8_t i = 0; i < MAX_PAIRED_COUNT; i++)
	{
		if(m_SavedData.pairedDevice[i].UID == UID)
			return true;
	}
	
	return false;
}

uint8_t BaseStation::getPairedCount()
{
	return m_SavedData.nNumPairedDevices;
}

void BaseStation::discovery()
{
	if((m_nLastDiscoveryPollTime + 500) < clockms())
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

void BaseStation::renameDevice(uint32_t UID, char* sNewName)
{
	for(uint8_t i = 0; i < MAX_PAIRED_COUNT; i++)
	{
		if(m_SavedData.pairedDevice[i].UID == UID)
		{
			memset(m_SavedData.pairedDevice[i].name, 0, REMOTE_NAME_LENGTH);
			strcpy(m_SavedData.pairedDevice[i].name, sNewName);
			return;
		}
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
	
	if(dst == m_SavedData.UID)
	{
		uint8_t cmd = *((uint8_t*)(buffer + MSG_TYPE));
		
		if(cmd == REMOTE_DISC_MSG || cmd == REMOTE_DISC_ACK || isPaired(src))
		{
			uint16_t size;
			memcpy((uint8_t*)buffer + MSG_LEN, &size, 2);
			
			handleCommand(cmd, src, buffer + MSG_PAYLOAD, size);
		}
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
	
	for(uint8_t i = 0; i < MAX_DISCOVERY; i++)
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
	memcpy(m_DiscoveredDevice[emptyIndex].name, name, REMOTE_NAME_LENGTH);
	m_nRemoteDiscovered++;
	
	print("ADDED DEVICE");
	
	return 0;
}

void BaseStation::addPairedDevice(uint32_t UID, char* sName)
{
	uint8_t emptyIndex = MAX_PAIRED_COUNT;
	
	print(__PRETTY_FUNCTION__);
	
	for(uint8_t i = 0; i < MAX_PAIRED_COUNT && emptyIndex == MAX_PAIRED_COUNT; i++)
	{
		if(m_SavedData.pairedDevice[i].UID == UID)
		{
			print("ALREADY PAIRED");
			return; //Device already paired
		}
		
		if(!m_SavedData.pairedDevice[i].UID && emptyIndex == MAX_PAIRED_COUNT)
			emptyIndex = i;
	}
	
	if(emptyIndex == MAX_PAIRED_COUNT)
	{
		print("NO ROOM");
		return; //No room left
	}
	
	m_SavedData.pairedDevice[emptyIndex].UID = UID;
	memcpy(m_SavedData.pairedDevice[emptyIndex].name, sName, REMOTE_NAME_LENGTH);
	m_SavedData.nNumPairedDevices++;
}