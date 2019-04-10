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
	
	virtual int write(const void* buf, uint8_t len);
	
	void background();
	
	protected:
	virtual uint32_t clockms();
	
	private:
	void discovery();
	
	private:
	bool m_bInDiscovery;
	uint32_t m_nDiscoveryTimeout;
	uint32_t m_nDiscoveryStartTime;
	uint8_t m_nRemoteDiscovered;
};

#endif