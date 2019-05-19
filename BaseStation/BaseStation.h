#ifndef __BASE_STATION_H__
#define __BASE_STATION_H__

#include <stdint.h>

#include "msgs.h"

#ifndef MAX_DISCOVERY
#define MAX_DISCOVERY   	16
#endif

class BaseStation
{
	public:
	BaseStation();
	~BaseStation();
	
	void startDiscovery(uint32_t timeout);
	virtual void stopDiscovery() = 0;
	uint8_t getDiscoveryCount();
	
	void background();
	
	bool pair(uint32_t UID, uint32_t timeout);
	
	protected:
	virtual uint32_t clockms() = 0;
	virtual void print(const char* str) = 0;
	virtual void print(int32_t num) = 0;
	virtual void printArr(void* buf, uint8_t len) = 0;
	
	virtual int write(const void* buf, uint16_t len) = 0;
	virtual int available() = 0;
	virtual int read(const void* buf, uint16_t len) = 0;
	
	virtual void save(uint16_t addr, const void* buffer, uint16_t len) = 0;
	virtual void load(uint16_t addr, const void* buffer, uint16_t len) = 0;
	
	void discovery();
	
	void handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len);
	
	protected:
	struct DISC_DEVICE
	{
		uint32_t UID;
		char name[REMOTE_NAME_LENGTH];
	};
	
	struct SAVED_DATA
	{
		uint8_t networkID[NETWORK_LEGNTH];
		char name[REMOTE_NAME_LENGTH];
		uint32_t UID;
		uint16_t checksum;
	};
	
	//Vars for discovery
	bool m_bInDiscovery;
	uint32_t m_nDiscoveryTimeout, m_nDiscoveryStartTime, m_nLastDiscoveryPollTime;
	uint8_t m_nRemoteDiscovered;
	
	uint16_t m_nMsgID;
	
	DISC_DEVICE m_DiscoveredDevice[MAX_DISCOVERY];
	SAVED_DATA m_SavedData;
	
	private:
	void handleMessage(const void* buffer, uint16_t len);
	
	void discoveryHandler(uint32_t src, const void* buffer, uint16_t len);
	void discoveryAckHandler(uint32_t src, const void* buffer, uint16_t len);
	
	uint8_t addDiscoveredDevice(uint32_t UID, char* name);
};

#endif