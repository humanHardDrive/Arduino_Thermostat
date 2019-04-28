#include "BaseStation.h"

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

void BaseStation::discovery()
{
}