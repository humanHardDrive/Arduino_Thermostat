#ifndef __MSGS_H__
#define __MSGS_H__

#define MAX_PAYLOAD_SIZE  128

struct MSG_BODY
{
  uint8_t cmd;
  uint8_t len;
  uint8_t payload[MAX_PAYLOAD_SIZE];
};

#define MSG_BODY_SIZE   sizeof(MSG_BODY)

enum CMD_TYPE
{
  /*COMMANDS*/
  NO_CMD = 0,
  GET_DEVICE_NAME,
  VERSION,
  MEM_READ,
  MEM_WRITE,
  SAVE,
  REBOOT,
  SET_AP_INFO,
  GET_AP_INFO,
  CONNECT_TO_AP,
  DISCONNECT_FROM_AP,
  START_AP,
  STOP_AP,
  START_NETWORK_HELPER,
  STOP_NETWORK_HELPER,
  GET_IP,
  SET_SERVER_INFO,
  GET_SERVER_INFO,
  CONNECT_TO_SERVER,
  DISCONNECT_FROM_SERVER,
  SET_PUB_ALIAS,
  SET_SUB_ALIAS,
  ADD_SUBSCRIPTION,
  REMOVE_SUBSCRIPTION,
  GET_CONNECTION_INFO,
  PUBLISH_INFO,
  TIME,
  SET_TIME_OFFSET,
  INVALID_CMD
};

enum NETWORK_STATE_CHANGE_TYPE
{
  NO_CHANGE = 0,
  DISCONNECTED,
  CONNECTING_TO_AP,
  CONNECTED_TO_AP,
  ACTING_AS_AP,
  UNKNOWN_STATE
};

#define MEM_PAGE_SIZE   64

struct MemPage
{
  uint16_t addr;
  uint8_t nCount;
  uint8_t block[MEM_PAGE_SIZE];
};

#define MAX_NETWORK_NAME_LENGTH   32
#define MAX_NETWORK_PASS_LENGTH   16

struct APInfo
{
  char sSSID[MAX_NETWORK_NAME_LENGTH];
  char password[MAX_NETWORK_PASS_LENGTH];
};

struct IPInfo
{
  uint8_t IP[4];
};

struct ServerInfo
{
  char sServerAddr[MAX_NETWORK_NAME_LENGTH];
  uint16_t nServerPort;

  char sUserName[MAX_NETWORK_NAME_LENGTH];
  char sUserPass[MAX_NETWORK_PASS_LENGTH];
};

#define MAX_ALIAS_NAME_LENGTH 16

struct AliasInfo
{
  uint8_t nIndex;
  char sAlias[MAX_ALIAS_NAME_LENGTH];
};

struct ConnectionInfo
{
  uint8_t nAPConnectionInfo;
  uint8_t nServerConnectionInfo;
};

#endif
