#ifndef __REMOTE_SENSOR_H__
#define __REMOTE_SENSOR_H__

#include <stdint.h>

#include "msgs.h"

class RemoteSensor
{
	public:
	RemoteSensor();
	~RemoteSensor();
	
	void background();
	
	void forget();
	void pair();
	
	protected:
	virtual uint32_t clockms() = 0;
	virtual void print(const char* str) = 0;
	
	virtual int write(const void* buffer, uint16_t len) = 0;
	virtual int available() = 0;
	virtual int read(const void* buffer, uint16_t len) = 0;
	
	virtual void save(uint16_t addr, const void* buffer, uint16_t len) = 0;
	virtual void load(uint16_t addr, const void* buffer, uint16_t len) = 0;
	
	public:
	private:
};

#endif