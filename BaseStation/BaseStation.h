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
	virtual void stopDiscovery() = 0;
	uint8_t getDiscoveryCount();
	
	void background();
	
	protected:
	virtual uint32_t clockms() = 0;
	virtual void print(const char* str) = 0;
	virtual void print(int32_t num) = 0;
	
	virtual int write(const void* buf, uint16_t len) = 0;
	virtual int available() = 0;
	virtual int read(const void* buf, uint16_t len) = 0;
	
	virtual void save(uint16_t addr, const void* buffer, uint16_t len) = 0;
	virtual void load(uint16_t addr, const void* buffer, uint16_t len) = 0;
	
	void discovery();
	
	protected:
	bool m_bInDiscovery;
	uint32_t m_nDiscoveryTimeout;
	uint32_t m_nDiscoveryStartTime;
	uint8_t m_nRemoteDiscovered;
};

#endif