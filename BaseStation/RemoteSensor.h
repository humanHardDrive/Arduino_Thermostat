#ifndef __REMOTE_SENSOR_H__
#define __REMOTE_SENSOR_H__

#include <stdint.h>

#include "msgs.h"

class RemoteSensor
{
	public:
	RemoteSensor();
	~RemoteSensor();
	
	void forget();
	void pair();
	
	virtual int write(const void* buffer, uint8_t len);
	
	private:
	
	public:
	private:
};

#endif