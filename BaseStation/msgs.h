#ifndef __MSGS_H__
#define __MSGS_H__

#include <stdint.h>

#define REMOTE_NAME_LENGTH	16
#define NETWORK_LEGNTH		8

#define SYSTEM_MSG_BASE		0x00
#define	REMOTE_INIT_MSG		SYSTEM_MSG_BASE + 1
#define REMOTE_DESC_MSG		SYSTEM_MSG_BASE + 2
#define PASSTHROUGH_MSG		SYSTEM_MSG_BASE + 3
#define REMOTE_DISC_MSG		SYSTEM_MSG_BASE + 4
#define REMOTE_DISC_ACK		SYSTEM_MSG_BASE + 5

typedef struct INIT_MSG
{
	uint32_t UID;
	uint8_t networkID[NETWORK_LEGNTH];
};

#define	USER_MSG_BASE		0x80

//Message layout
#define HEADER_SIZE	0x0C
#define MSG_DST		0x00
#define MSG_SRC		0x04
#define MSG_ID		0x08
#define MSG_LEN		0x0A
#define MSG_TYPE	0x0B
#define MSG_PAYLOAD	0x0C

#endif