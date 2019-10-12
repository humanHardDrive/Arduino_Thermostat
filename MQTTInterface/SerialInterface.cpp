#include "SerialInterface.h"

SerialInterface::SerialInterface()
{
}

SerialInterface::~SerialInterface() =
  default;

void SerialInterface::update(uint8_t c)
{
  if ((millis() - m_LastRXTime) > 10 &&
      m_ParseState != WAITING_FOR_STX)
    m_ParseState = WAITING_FOR_STX;

  m_LastRXTime = millis();

  m_StateFn[m_ParseState](c);
}

void SerialInterface::WaitingForSTXState(uint8_t c)
{
  if (c == SERIAL_STX)
  {
    m_ParseState = WAITING_FOR_CMD;
    memset(m_CurrentCommand, 0, 2);
    m_CommandDataCount = 0;
  }
}

void SerialInterface::WaitingForCMDState(uint8_t c)
{
  if (!m_CurrentCommand[0])
    m_CurrentCommand[0] = (char)c;
  else if (!m_CurrentCommand[1])
  {
    m_CurrentCommand[1] = c;
    m_ParseState = WAITING_FOR_LEN;
  }
}

void SerialInterface::WaitingForLenState(uint8_t c)
{
  m_CurrentCommandLen = c;

  if (m_CurrentCommandLen)
    m_ParseState = WAITING_FOR_DATA;
  else
    m_ParseState = WAITING_FOR_ETX;
}

void SerialInterface::WaitingForDataState(uint8_t c)
{
  m_CurrentCommandBuf[m_CommandDataCount] = c;
  m_CommandDataCount++;

  if (m_CommandDataCount >= m_CurrentCommandLen)
    m_ParseState = WAITING_FOR_ETX;
}

void SerialInterface::WaitingForETXState(uint8_t c)
{
  if (c == SERIAL_ETX)
  {
    std::pair<char, char> cmd(m_CurrentCommand[0], m_CurrentCommand[1]);

    m_ParseState = WAITING_FOR_STX;

    if (m_CmdHandler.find(cmd) != m_CmdHandler.end())
      m_CmdHandler[cmd](m_CurrentCommandBuf, m_CurrentCommandLen);

  }
}
