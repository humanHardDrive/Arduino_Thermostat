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
	*(outBuf + MSG_ID) = msgType;
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
}