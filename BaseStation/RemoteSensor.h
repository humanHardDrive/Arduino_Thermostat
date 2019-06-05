#ifndef __REMOTE_SENSOR_H__
#define __REMOTE_SENSOR_H__

#include <stdint.h>

#include "CommBase.h"
#include "msgs.h"

class RemoteSensor
{
	public:
	RemoteSensor();
	~RemoteSensor();
	
	void background();
	
	void forget();
	void pair(uint16_t timeout);
	
	bool isPairing() const {return m_bInDiscovery;}
	
	virtual bool recover() = 0;
	virtual void reset(bool nv) = 0;
	
	protected:
	virtual uint32_t clockms() = 0;
	virtual void print(const char* str) = 0;
	virtual void print(int32_t num) = 0;
	
	virtual int write(const void* buffer, uint16_t len) = 0;
	virtual int available() = 0;
	virtual int read(const void* buffer, uint16_t len) = 0;
	
	virtual void save() = 0;
	
	virtual void seedRnd(uint16_t seed) = 0;
	virtual uint16_t rnd() = 0;
	
	virtual void updateNetwork() = 0;
	
	virtual void handleCommand(uint8_t cmd, const void* buffer, uint16_t len);
	
	protected:
	struct SAVED_DATA
	{
		uint8_t networkID[NETWORK_LEGNTH];
		char name[REMOTE_NAME_LENGTH];
		uint32_t UID, baseUID;
		uint16_t checksum;
	};
	
	SAVED_DATA m_SavedData;
	
	bool m_bInDiscovery;
	uint16_t m_nMsgID;
	
	public:
	
	private:
	void discoveryBackground();
	
	void handleMessage(const void* buffer, uint16_t len);
	
	void discoveryHandler(const void* buffer, uint16_t len);
	void discoveryAckHandler(const void* buffer, uint16_t len);
	void deviceInitHandler(const void* buffer, uint16_t len);
	
	private:
	uint32_t m_nPairStartTime, m_nDiscoveryMsgTime;
	uint16_t m_nDiscoveryTimeout;
	uint8_t m_nDiscoveryRspDelay;
};

#endif