#ifndef __COMM_BASE__
#define __COMM_BASE__

#include<stdint.h>

void buildPacket(uint8_t msgType, uint16_t* msgID, uint32_t src, uint32_t dst, uint8_t* payload,
				 uint16_t len, uint8_t* outBuf, uint16_t* outLen);
				 
void buildPacket(uint8_t msgType, uint16_t msgID, uint32_t src, uint32_t* dst, uint8_t dstCount,
				 uint8_t* payload, uint16_t len, uint8_t* outBuf, uint16_t* outLen);

#endif