#include "BaseStation.h"

#include <string.h>

BaseStation::BaseStation()
{
	m_bInDiscovery = false;
}

BaseStation::~BaseStation()
{
}

void BaseStation::startDiscovery(uint32_t timeout)
{
	m_nDiscoveryTimeout = timeout;
	m_nDiscoveryStartTime = clockms();
	m_nRemoteDiscovered = 0;
	
	m_bInDiscovery = true;
}

void BaseStation::stopDiscovery()
{
	m_bInDiscovery = false;
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
		if((m_nDiscoveryStartTime + m_nDiscoveryTimeout) > clockms())
			m_bInDiscovery = false;
	}
}

void BaseStation::sendMsg(uint8_t dst, uint8_t cmd, uint8_t len, uint8_t* payload)
{
	uint8_t tempBuffer[128];
	
	tempBuffer[MSG_DST] = dst;
	tempBuffer[MSG_SRC] = 0;
	tempBuffer[MSG_ID] = 0;
	tempBuffer[MSG_ID + 1] = 0;
	tempBuffer[MSG_TYPE] = cmd;
	tempBuffer[MSG_LEN] = len;
	tempBuffer[MSG_LEN + 1] = 0;
	
	memcpy((tempBuffer + MSG_PAYLOAD), payload, len);
	write(tempBuffer, (MSG_HEADER_SIZE + len));
}

void BaseStation::discovery()
{
}