#include "ESPInterface.h"

ESPInterface::ESPInterface() :
  m_CommandBufQIn(0),
  m_CommandBufQOut(0),
  m_CommandBufQCount(0)
{
}

ESPInterface::~ESPInterface()
{
}

void ESPInterface::background(uint8_t c)
{
  if ((millis() - m_LastRXTime) > 10 &&
      m_ParseState != WAITING_FOR_STX)
    m_ParseState = WAITING_FOR_STX;

  m_LastRXTime = millis();
  (this->*m_StateFn[m_ParseState])(c);
}

void ESPInterface::sendCommand(uint8_t cmd, void* buf, uint8_t len)
{
  MSG_BODY msg;

  if (len > MAX_PAYLOAD_SIZE)
    len = MAX_PAYLOAD_SIZE;

  if (buf && len)
    memcpy(msg.payload, buf, len);
  else
    len = 0;

  msg.cmd = cmd;
  msg.len = len;

  Serial.write(SERIAL_STX);
  Serial.write(msg.cmd);
  Serial.write(msg.len);
  Serial.write(msg.payload, msg.len);
  Serial.write(SERIAL_ETX);
}

bool ESPInterface::messageReady(uint8_t* pCmd, void** buf)
{
  if (m_CommandBufQCount)
  {
    *pCmd = m_CurrentCommand;
    *buf = m_CommandBufQ[m_CommandBufQOut];

    m_CommandBufQOut++;
    if(m_CommandBufQOut >= COMMAND_QUEUE_SIZE)
      m_CommandBufQOut = 0;
    
    m_CommandBufQCount--;
    return true;
  }

  return false;
}

void ESPInterface::WaitingForSTXState(uint8_t c)
{
  if (c == SERIAL_STX)
  {
    m_ParseState = WAITING_FOR_CMD;

    //Reset the current command code and the number of
    //bytes received
    m_CurrentCommand =
      m_CommandDataCount = 0;
    memset(m_CommandBufQ[m_CommandBufQIn], 0, COMMAND_BUFFER_LEN);
  }
}

void ESPInterface::WaitingForCMDState(uint8_t c)
{
  m_CurrentCommand = c;
  m_ParseState = WAITING_FOR_LEN;
}

void ESPInterface::WaitingForLenState(uint8_t c)
{
  //TODO: limit this number to the buffer size
  m_CurrentCommandLen = c;

  if (m_CurrentCommandLen)
    m_ParseState = WAITING_FOR_DATA;
  else
    //If there's no data to be sent, just jump to the end state
    m_ParseState = WAITING_FOR_ETX;
}

void ESPInterface::WaitingForDataState(uint8_t c)
{
  //Add data to the buffer
  m_CommandBufQ[m_CommandBufQIn][m_CommandDataCount] = c;
  m_CommandDataCount++;

  if (m_CommandDataCount >= m_CurrentCommandLen)
    m_ParseState = WAITING_FOR_ETX;
}

void ESPInterface::WaitingForETXState(uint8_t c)
{
  bool incQ = false;
  
  if (c == SERIAL_ETX)
  {
    m_ParseState = WAITING_FOR_STX;
    incQ = true;
  }
  else if (c == SERIAL_STX)
  {
    WaitingForSTXState(c);
    incQ = true;
  }

  if(incQ)
  {
    m_CommandBufQCount++;
    
    m_CommandBufQIn++;
    if(m_CommandBufQIn >= COMMAND_QUEUE_SIZE)
      m_CommandBufQIn = 0;
  }
}
