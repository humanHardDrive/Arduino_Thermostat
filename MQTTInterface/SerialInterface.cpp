#include "SerialInterface.h"

SerialInterface::SerialInterface()
{
}

SerialInterface::~SerialInterface() =
  default;

void SerialInterface::update(uint8_t c)
{
  //Reset the parse state if a character hasn't been received
  //in 10ms
  //TODO: remove the magic number 10
  if ((millis() - m_LastRXTime) > 10 &&
      m_ParseState != WAITING_FOR_STX)
    m_ParseState = WAITING_FOR_STX;

  m_LastRXTime = millis();

  //Call the appropriate state handler
  //TODO: bounds check the current parse state
  m_StateFn[m_ParseState](c);
}

void SerialInterface::setCommandHandler(char c1, char c2, std::function<void(uint8_t*, uint8_t)> fn)
{
  std::pair<char, char> cmd(toupper(c1), toupper(c2));

  m_CmdHandler[cmd] = fn;
}

void SerialInterface::WaitingForSTXState(uint8_t c)
{
  if (c == SERIAL_STX)
  {
    m_ParseState = WAITING_FOR_CMD;

    //Reset the current command code and the number of
    //bytes received
    memset(m_CurrentCommand, 0, 2);
    m_CommandDataCount = 0;
    //The data buffer isn't reset because only the number of bytes
    //written is needed
  }
}

//TODO: Ensure that the character received is alpha-numeric
//A parameter of 0 is NOT allowed
void SerialInterface::WaitingForCMDState(uint8_t c)
{
  if (!m_CurrentCommand[0]) //Have we gotten the first character?
    m_CurrentCommand[0] = toupper((char)c);
  else if (!m_CurrentCommand[1]) //What about the second?
  {
    m_CurrentCommand[1] = toupper((char)c);
    m_ParseState = WAITING_FOR_LEN;
  }
}

void SerialInterface::WaitingForLenState(uint8_t c)
{
  //TODO: limit this number to the buffer size
  m_CurrentCommandLen = c;

  if (m_CurrentCommandLen)
    m_ParseState = WAITING_FOR_DATA;
  else
    //If there's no data to be sent, just jump to the end state
    m_ParseState = WAITING_FOR_ETX;
}

void SerialInterface::WaitingForDataState(uint8_t c)
{
  //Add data to the buffer
  m_CurrentCommandBuf[m_CommandDataCount] = c;
  m_CommandDataCount++;

  if (m_CommandDataCount >= m_CurrentCommandLen)
    m_ParseState = WAITING_FOR_ETX;
}

void SerialInterface::WaitingForETXState(uint8_t c)
{
  if (c == SERIAL_ETX)
  {
    //Put the array into a pair
    std::pair<char, char> cmd(m_CurrentCommand[0], m_CurrentCommand[1]);

    m_ParseState = WAITING_FOR_STX;

    //If a handler exists for this command code, call it
    if (m_CmdHandler.find(cmd) != m_CmdHandler.end())
      m_CmdHandler[cmd](m_CurrentCommandBuf, m_CurrentCommandLen);
  }
}
