#include "RemoteSensor.h"

RemoteSensor::RemoteSensor()
{
}

RemoteSensor::~RemoteSensor()
{
}

void RemoteSensor::background()
{
	uint8_t buffer[128];
	uint16_t size;
	
	if(available())
	{
		size = read(buffer, sizeof(buffer));
	}
}

void RemoteSensor::forget()
{
}

void RemoteSensor::pair()
{
	print(__PRETTY_FUNCTION__);
}