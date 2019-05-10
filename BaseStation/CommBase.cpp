#include "CommBase.h"
#include "msgs.h"

#include <string.h>

void buildPacket(uint8_t msgType, uint16_t msgID, uint32_t src, uint32_t dst, uint8_t* payload,
				 uint16_t len, uint8_t* outBuf, uint16_t* outLen)
{
	memcpy(outBuf + MSG_DST, &dst, 4);
	memcpy(outBuf + MSG_SRC, &src, 4);
	memcpy(outBuf + MSG_ID, &m_nMsgID, 2);
	memcpy(outBuf + MSG_LEN, &len, 2);
	*(outBuf + MSG_TYPE) = msgType;
	
	if(payload)
		memcpy(outBuf + MSG_PAYLOAD, payload, len);
	
	*outLen = len + HEADER_SIZE;
}

void buildPacket(uint8_t msgType, uint16_t msgID, uint32_t src, uint32_t* dst, uint8_t* payload,
				 uint16_t len, uint8_t* outBuf, uint16_t* outLen)
{
	memcpy(outBuf + MSG_DST, &dst, 4);
	memcpy(outBuf + MSG_SRC, &src, 4);
	memcpy(outBuf + MSG_ID, &m_nMsgID, 2);
	memcpy(outBuf + MSG_LEN, &len, 2);
	*(outBuf + MSG_TYPE) = msgType;
	
	if(payload)
		memcpy(outBuf + MSG_PAYLOAD, payload, len);
	
	*outLen = len + HEADER_SIZE;
}