#include <Arduino.h>
#include <functional>
#include <map>

#define SERIAL_STX  0x55
#define SERIAL_ETX  0xAA

#define COMMAND_BUFFER_LEN    128

class SerialInterface
{
  public:
    SerialInterface();
    ~SerialInterface();

    void update(uint8_t c);

    void setCommandHandler(char c1, char c2, std::function<void(uint8_t*, uint8_t)>);

  private:
    enum PARSE_STATE
    {
      WAITING_FOR_STX = 0, //Waiting for the STX character to come over serial
      WAITING_FOR_CMD,  //Collecting the 2 letter command code
      WAITING_FOR_LEN,  //Getting the total number of characters in the data frame
      WAITING_FOR_DATA, //Actual data for the command
      WAITING_FOR_ETX,  //Waiting for the character to restart transmission
      ALL_PARSE_STATES
    };

    uint8_t m_ParseState = WAITING_FOR_STX;

    uint32_t m_LastRXTime = 0;

    char m_CurrentCommand[2];
    uint8_t m_CurrentCommandLen;
    uint8_t m_CommandDataCount;
    uint8_t m_CurrentCommandBuf[COMMAND_BUFFER_LEN];

    void WaitingForSTXState(uint8_t);
    void WaitingForCMDState(uint8_t);
    void WaitingForLenState(uint8_t);
    void WaitingForDataState(uint8_t);
    void WaitingForETXState(uint8_t);

    //Function handlers for each of the 2 letter commands
    //These are configured by the caller
    std::map<std::pair<char, char>, std::function<void(uint8_t*, uint8_t)>> m_CmdHandler;

    //Function handlers for all of the serial parse states
    std::function<void(uint8_t)> m_StateFn[ALL_PARSE_STATES] =
    {
      std::bind(&SerialInterface::WaitingForSTXState, this, std::placeholders::_1),
      std::bind(&SerialInterface::WaitingForCMDState, this, std::placeholders::_1),
      std::bind(&SerialInterface::WaitingForLenState, this, std::placeholders::_1),
      std::bind(&SerialInterface::WaitingForDataState, this, std::placeholders::_1),
      std::bind(&SerialInterface::WaitingForETXState, this, std::placeholders::_1)
    };
};
