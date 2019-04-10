#ifndef __BASE_STATION_H__
#define __BASE_STATION_H__

#include <stdint.h>

#include "msgs.h"

class BaseStation
{
	public:
	BaseStation();
	~BaseStation();
	
	void startDiscovery(uint32_t timeout);
	void stopDiscovery();
	uint8_t getDiscoveryCount();
	
	void background();
	
	virtual int write(const void* buf, uint16_t len) = 0;
	
	protected:
	virtual uint32_t clockms() = 0;
	
	private:
	void discovery();
	
	private:
	bool m_bInDiscovery;
	uint32_t m_nDiscoveryTimeout;
	uint32_t m_nDiscoveryStartTime;
	uint8_t m_nRemoteDiscovered;
};

#endif