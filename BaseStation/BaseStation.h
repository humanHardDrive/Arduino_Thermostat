#ifndef __BASE_STATION_H__
#define __BASE_STATION_H__

#include <stdint.h>

#include "msgs.h"

#define MAX_DISCOVERY   	16
#define MAX_PAIRED_COUNT	8

class BaseStation
{
	public:
	BaseStation();
	~BaseStation();
	
	void startDiscovery(uint32_t timeout);
	virtual void stopDiscovery() = 0;
	uint8_t getDiscoveryCount();
	
	void background();
	
	bool pair(uint32_t UID, char* sName, uint32_t timeout);
	bool unpair(uint32_t UID);
	bool isPaired(uint32_t UID);
	uint8_t getPairedCount();
	
	virtual bool recover() = 0;
	virtual void reset(bool nv) = 0;
	
	protected:
	virtual uint32_t clockms() = 0;
	virtual void print(const char* str) = 0;
	virtual void print(int32_t num) = 0;
	virtual void printArr(void* buf, uint8_t len) = 0;
	
	virtual int write(const void* buf, uint16_t len) = 0;
	virtual int available() = 0;
	virtual int read(const void* buf, uint16_t len) = 0;
	
	virtual void save() = 0;
	
	void discovery();
	
	void renameDevice(uint32_t UID, char* sNewName);
	
	virtual void handleCommand(uint8_t cmd, uint32_t src, const void* buffer, uint16_t len);
	
	uint16_t calcChecksum(uint8_t* ptr, uint16_t len);
	
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
		
		DISC_DEVICE pairedDevice[MAX_PAIRED_COUNT];
		uint8_t nNumPairedDevices;
		
		uint16_t checksum;
	};
	
	SAVED_DATA m_SavedData;
	
	DISC_DEVICE m_DiscoveredDevice[MAX_DISCOVERY];
	
	//Vars for discovery
	bool m_bInDiscovery;
	uint32_t m_nDiscoveryTimeout, m_nDiscoveryStartTime, m_nLastDiscoveryPollTime;
	uint8_t m_nRemoteDiscovered;
	
	uint16_t m_nMsgID;
	
	private:
	void handleMessage(const void* buffer, uint16_t len);
	
	void discoveryHandler(uint32_t src, const void* buffer, uint16_t len);
	void discoveryAckHandler(uint32_t src, const void* buffer, uint16_t len);
	
	uint8_t addDiscoveredDevice(uint32_t UID, char* name);
	void addPairedDevice(uint32_t UID, char* sName);
};

#endif