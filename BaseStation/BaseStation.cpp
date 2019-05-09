#include "BaseStation.h"

#include <string.h>

BaseStation::BaseStation()
{
	m_bInDiscovery = false;
	m_nMsgID = 0;
}

BaseStation::~BaseStation()
{
}

void BaseStation::buildPacket(uint8_t msgType, uint8_t src, uint8_t dst, uint8_t* payload, uint16_t len, uint8_t* outBuf, uint16_t* outLen)
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

void BaseStation::buildPacket(uint8_t msgType, uint8_t src, uint8_t* dst, uint8_t* payload, uint16_t len, uint8_t* outBuf, uint16_t* outLen)
{

}

void BaseStation::startDiscovery(uint32_t timeout)
{
	print(__PRETTY_FUNCTION__);
	
	m_nDiscoveryTimeout = timeout;
	m_nDiscoveryStartTime = clockms();
	m_nRemoteDiscovered = 0;
	m_nLastDiscoveryPollTime = 0;
	
	print(m_nDiscoveryTimeout);
	print(m_nDiscoveryStartTime);
	
	m_bInDiscovery = true;
}

uint8_t BaseStation::getDiscoveryCount()
{
	return m_nRemoteDiscovered;
}

void BaseStation::background()
{
	if(m_bInDiscovery)
	{
		discovery();
		if((m_nDiscoveryStartTime + m_nDiscoveryTimeout) < clockms())
		{
			m_bInDiscovery = false;
			stopDiscovery();
		}
	}
}

void BaseStation::discovery()
{
	if((m_nLastDiscoveryPollTime + 100) < clockms())
	{
		uint8_t DiscoverMsg[16];
		uint16_t MsgSize;
		
		buildPacket((uint8_t)(REMOTE_DISC_MSG), (uint8_t)0, (uint8_t)0, NULL, (uint16_t)0, DiscoverMsg, &MsgSize);
		write(DiscoverMsg, MsgSize);
	}
	
	if(available())
	{
		uint8_t rspBuffer[16];
		uint16_t rspLen;
		
		rspLen = read(rspBuffer, 16);
		handleMessage(rspBuffer, rspLen);
	}
}

void BaseStation::handleCommand(uint8_t cmd, const void* buffer, uint16_t len)
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
		break;
		
		case REMOTE_DISC_ACK:
		print("ACK");
		break;
	}
}

void BaseStation::handleMessage(const void* buffer, uint16_t len)
{
	uint8_t dst = *((uint8_t*)(buffer + MSG_DST));
	
	if(!dst)
	{
		uint8_t cmd = *((uint8_t*)(buffer + MSG_TYPE));
		uint16_t size;
		memcpy(buffer + MSG_LEN, &size, 2);
		
		handleCommand(cmd, buffer + MSG_PAYLOAD, size);
	}
}