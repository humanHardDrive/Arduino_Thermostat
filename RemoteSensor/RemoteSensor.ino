#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <EEPROM.h>
#include <map>
#include <Wire.h>
#include "Adafruit_MCP23008.h"

#include "SensorDevice.h"

/*Default sleep time is 5 minutes*/
#define DEFAULT_SLEEP_TIME_S  (5*60)
#define DEFAULT_SLEEP_TIME_MS (DEFAULT_SLEEP_TIME_S*1000)
#define DEFAULT_SLEEP_TIME_US (DEFAULT_SLEEP_TIME_MS*1000)
#define WAKE_TIME_S           (10)
#define WAKE_TIME_MS          (WAKE_TIME_S*1000)

#define DEBOUNCE_TIME         15

#define MAX_DEVICE_NAME_LENGTH    32
#define MAX_PATH_LENGTH           32

#define DEVICE_NAME_BASE          "remoteSensor-"

//Native GPIO
//All of the native GPIO are used as output
enum
{
  FLASH_PIN = 0,
  RADIO_TX,
  RESERVED_PIN_2,
  RADIO_RX,
  HB_LED_PIN,
  BATT_LED_PIN,
  RESERVED_PIN_6,
  RESERVED_PIN_7,
  RESERVED_PIN_8,
  SCL_PIN,
  SDA_PIN,
  RESERVED_PIN_11,
  SLEEP_PIN,
  EXP_RST_PIN,
  UNUSED_PIN_14,
  RESERVED_PIN_15,
  RST_PIN,
  ALL_NATIVE_PINS
};

#define TEMP_SENSE_PIN  A0

//Expander GPIO
//All of the expander GPIO is used as input
enum
{
  UP_BTN_PIN = 0,
  DOWN_BTN_PIN,
  CENTER_BTN_PIN,
  BATT_STS_PIN,
  CHARGE_STS_PIN,
  CHARGER_STS_PIN,
  SLEEP_STS_PIN,
  WAKE_STS_PIN,
  ALL_EXP_PINS
};

Adafruit_MCP23008 ioExp;
uint8_t aPinDebounce[ALL_EXP_PINS];
bool aPinStatus[ALL_EXP_PINS];

enum RUNNING_STATE : uint8_t
{
  SAMPLE = 0,
  TURN_WIFI_ON, //WIFI_OFF taken
  WAIT_FOR_WIFI_ON,
  CONNECT_TO_NETWORK,
  WAIT_FOR_NETWORK,
  MQTT_CONNECT,
  WAIT_FOR_MQTT_CONNECT,
  UPDATE_LOCAL_VARIABLES,
  POST_VARIABLES,
  SLEEP_START,
  MQTT_DISCONNECT,
  WAIT_FOR_MQTT_DISCONNECT,
  TURN_WIFI_OFF,
  WAIT_FOR_WIFI_OFF,
  SLEEP,
  ALL_STATES
};

struct SaveInfo
{
  public:
    char sDeviceName[MAX_DEVICE_NAME_LENGTH];

    char sNetworkName[16];
    char sNetworkPass[16];

    char sServerURL[16];
    uint16_t nServerPort;
    char sServerUser[16];
    char sServerPass[16];

    char sRemoteDevicePath[MAX_PATH_LENGTH];

    char sAmbientTempPath[MAX_PATH_LENGTH];
    char sTargetTempPath[MAX_PATH_LENGTH];

    char sRequestedModePath[MAX_PATH_LENGTH];
    char sCurrentModePath[MAX_PATH_LENGTH];

    void makeChecksum()
    {
      //Set the current checksum to 0 to not interfere with the calculation
      this->nChecksum = 0;
      this->nChecksum = calcChecksum();
    }

    bool isValid()
    {
      uint16_t cChecksum;
      uint16_t nChecksum = this->nChecksum;
      //Set the current checksum to 0 before validating
      this->nChecksum = 0;
      cChecksum = calcChecksum();
      this->nChecksum = nChecksum;
      return (cChecksum == nChecksum);
    }

  private:
    uint16_t nChecksum;

    uint16_t calcChecksum()
    {
      uint16_t checksum = 0;
      for (size_t i = 0; i < sizeof(SaveInfo); i++)
        checksum += ((uint8_t*)this)[i];

      //Calculate the 2's complement so that an emtpy structure isn't valid
      return ((~checksum) + 1);
    }
};

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
SensorDevice sensor(TEMP_SENSE_PIN, 100);

//SavedInfo is what is currently in storage
//WorkingInfo is what is modified during runtime
SaveInfo savedInfo, workingInfo;

uint32_t ulSleepTime = DEFAULT_SLEEP_TIME_US;
uint32_t ulWakeTimeStart = 0;
uint32_t ulConnectionTimer = 0;

uint8_t currentRunningState = RUNNING_STATE::SAMPLE;

//The remote device name can be overwritten by MQTT notification
//This flag isn't
bool bBecomeRemoteDevice = false;
char sRemoteDeviceName[MAX_DEVICE_NAME_LENGTH];

const char sHexMap[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void buildDeviceName(char* sName)
{
  /*Use the chip ID to build a unique identifier*/
  /*Makes sense to use the one built in instead of creating a new one*/
  uint32_t nID = ESP.getChipId();
  char sID[MAX_DEVICE_NAME_LENGTH];
  strcpy(sName, DEVICE_NAME_BASE);

  memset(sID, 0, MAX_DEVICE_NAME_LENGTH);
  /*The chip ID is 3 bytes, so 6 hex characters*/
  for (uint8_t i = 0; i < 6; i++)
  {
    /*Reverse the bit order*/
    sID[5 - i] = sHexMap[nID & 0x0F];
    nID >>= 4;
  }

  strcat(sName, sID);
}

void setupEEPROM()
{
  uint32_t eepromSize = 0;

  eepromSize += sizeof(SaveInfo);
  eepromSize += sensor.size();

  EEPROM.begin(eepromSize);
}

bool recoverSaveInfo()
{
  bool bRetVal = true;
  EEPROM.get(0, workingInfo);

  if (!workingInfo.isValid())
  {
    bRetVal = false;

    //Put everything back
    memset(&workingInfo, 0, sizeof(SaveInfo));
    //Build a device name
    buildDeviceName(workingInfo.sDeviceName);
    workingInfo.makeChecksum();
  }

  //Copy back the working info
  memcpy(&savedInfo, &workingInfo, sizeof(SaveInfo));

  return bRetVal;
}

void setup()
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  ioExp.begin();

  //Setup native IO
  pinMode(HB_LED_PIN, OUTPUT);
  pinMode(SLEEP_PIN, OUTPUT);
  pinMode(EXP_RST_PIN, OUTPUT);
  pinMode(BATT_LED_PIN, OUTPUT);
  //Setup initial pin states
  pinMode(SLEEP_PIN, LOW);
  pinMode(HB_LED_PIN, HIGH);
  pinMode(EXP_RST_PIN, HIGH);
  pinMode(BATT_LED_PIN, LOW);

  //Setup expander IO
  //Reset the expander first
  pinMode(EXP_RST_PIN, LOW);
  delay(5);
  pinMode(EXP_RST_PIN, HIGH);
  //These pins need pullups
  ioExp.pinMode(UP_BTN_PIN, INPUT);
  ioExp.pinMode(DOWN_BTN_PIN, INPUT);
  ioExp.pinMode(CENTER_BTN_PIN, INPUT);
  ioExp.pullUp(UP_BTN_PIN, HIGH);
  ioExp.pullUp(DOWN_BTN_PIN, HIGH);
  ioExp.pullUp(CENTER_BTN_PIN, HIGH);
  //These pins already have pullups
  ioExp.pinMode(BATT_STS_PIN, INPUT);
  ioExp.pinMode(CHARGE_STS_PIN, INPUT);
  ioExp.pinMode(CHARGER_STS_PIN, INPUT);
  ioExp.pinMode(SLEEP_STS_PIN, INPUT);
  ioExp.pinMode(WAKE_STS_PIN, INPUT);

  //Setup non-volatile storage
  setupEEPROM();
  recoverSaveInfo();

  memset(aPinDebounce, 0, sizeof(aPinDebounce));
  memset(aPinStatus, 0, sizeof(aPinStatus));
  memset(sRemoteDeviceName, 0, MAX_DEVICE_NAME_LENGTH);

  ulWakeTimeStart = millis();
}

unsigned long ulLastHBUpdate = 0;
unsigned long ulLastBattUpdate = 0;
void updateStatusLED()
{
  //Charger is on
  if (aPinStatus[CHARGER_STS_PIN])
  {
    //HB led is always active
    digitalWrite(HB_LED_PIN, HIGH);
    ulLastHBUpdate = millis();

    //Toggle the battery indication LED until charged
    //Battery is charging
    if (aPinStatus[CHARGE_STS_PIN])
    {
      //Toggle the battery status LED every 0.5 second while charging
      if ((millis() - ulLastBattUpdate) > 500)
      {
        if (digitalRead(BATT_LED_PIN))
          digitalWrite(BATT_LED_PIN, LOW);
        else
          digitalWrite(BATT_LED_PIN, HIGH);

        ulLastBattUpdate = millis();
      }
    }
    else //Charged
    {
      digitalWrite(BATT_LED_PIN, HIGH);
      ulLastBattUpdate = millis();
    }
  }
  else
  {
    //Toggle the heartbeat LED every 1 second
    if ((millis() - ulLastHBUpdate) > 1000)
    {
      if (digitalRead(HB_LED_PIN))
        digitalWrite(HB_LED_PIN, LOW);
      else
        digitalWrite(HB_LED_PIN, HIGH);

      ulLastHBUpdate = millis();
    }

    //Update the battery indicator LED to show low voltage
    digitalWrite(BATT_LED_PIN, !aPinStatus[BATT_STS_PIN]);
  }
}

void onUpBtnStateChanged()
{
  ulWakeTimeStart = millis();
}

void onDownBtnStateChanged()
{
  ulWakeTimeStart = millis();
}

void onCenterBtnStateChanged()
{
  ulWakeTimeStart = millis();
}

std::map<uint8_t, std::function<void(void)>> pinUpdateFn =
{
  {UP_BTN_PIN, onUpBtnStateChanged},
  {DOWN_BTN_PIN, onDownBtnStateChanged},
  {CENTER_BTN_PIN, onCenterBtnStateChanged}
};

uint32_t ulLastIOUpdateTime = 0;
void updateInputs()
{
  if((millis() - ulLastIOUpdateTime) < 1000)
    return;
  
  for(size_t i = 0; i < ALL_EXP_PINS; i++)
  {
    //Debounce the input
    if(ioExp.digitalRead(i) && aPinDebounce[i] < DEBOUNCE_TIME)
      aPinDebounce[i]++;
    else if(!ioExp.digitalRead(i) && aPinDebounce[i])
      aPinDebounce[i]--;

    //Update the state
    if(!aPinDebounce[i] && aPinStatus[i])
    {
      aPinStatus[i] = false;
      //Call the handler if it exists
      if(pinUpdateFn[i])
        pinUpdateFn[i]();
    }
    else if(aPinDebounce[i] >= DEBOUNCE_TIME && !aPinStatus[i])
    {
      aPinStatus[i] = true;
      //Call the handler if it exists
      if(pinUpdateFn[i])
        pinUpdateFn[i]();
    }
  }

  ulLastIOUpdateTime = millis();
}

uint8_t SampleStateFn()
{
  sensor.update();

  if ((millis() - ulWakeTimeStart) > WAKE_TIME_MS)
    return RUNNING_STATE::TURN_WIFI_ON;

  return RUNNING_STATE::SAMPLE;
}

uint8_t WifiOnStateFn()
{
  //Check if there's a network to connect to
  if (workingInfo.sNetworkName[0])
  {
    WiFi.mode(WIFI_STA);
    ulConnectionTimer = millis();

    return RUNNING_STATE::WAIT_FOR_WIFI_ON;
  }

  //Just skip to sleep
  return RUNNING_STATE::SLEEP_START;
}

uint8_t WaitForWifiOnStateFn()
{
  if (WiFi.getMode() == WIFI_STA)
    return RUNNING_STATE::CONNECT_TO_NETWORK;

  //If the mode doesn't change, just go to sleep
  if ((millis() - ulConnectionTimer) > 250)
    return RUNNING_STATE::SLEEP_START;

  return RUNNING_STATE::WAIT_FOR_WIFI_ON;
}

uint8_t ConnectToNetworkStateFn()
{
  WiFi.begin(workingInfo.sNetworkName, workingInfo.sNetworkPass);
  ulConnectionTimer = millis();

  return RUNNING_STATE::WAIT_FOR_NETWORK;
}

uint8_t WaitForNetworkStateFn()
{
  if (WiFi.status() == WL_CONNECTED)
    return RUNNING_STATE::MQTT_CONNECT;

  return RUNNING_STATE::WAIT_FOR_NETWORK;
}

void MQTTCallback(char* sTopic, byte* pPayload, unsigned int length)
{

}

uint8_t MQTTConnectStateFn()
{
  //Make sure all relavent info is setup to connect to MQTT server
  if (workingInfo.sServerURL[0] && workingInfo.nServerPort
      && workingInfo.sDeviceName
      && workingInfo.sRemoteDevicePath[0]
      && workingInfo.sAmbientTempPath[0]
      && workingInfo.sTargetTempPath[0]
      && workingInfo.sRequestedModePath[0]
      && workingInfo.sCurrentModePath[0])
  {
    mqttClient.setServer(workingInfo.sServerURL, workingInfo.nServerPort);
    mqttClient.setCallback(MQTTCallback);
    mqttClient.connect(workingInfo.sDeviceName);

    ulConnectionTimer = millis();

    return RUNNING_STATE::WAIT_FOR_MQTT_CONNECT;
  }

  return RUNNING_STATE::SLEEP_START;
}

uint8_t WaitForMQTTConnectStateFn()
{
  //Should only reach here if subscription info is setup
  if (mqttClient.connected())
  {
    mqttClient.subscribe(workingInfo.sRemoteDevicePath);
    mqttClient.subscribe(workingInfo.sTargetTempPath);
    mqttClient.subscribe(workingInfo.sCurrentModePath);

    ulConnectionTimer = millis();

    return RUNNING_STATE::UPDATE_LOCAL_VARIABLES;
  }

  if ((millis() - ulConnectionTimer) > 1000)
    return RUNNING_STATE::SLEEP_START;

  return RUNNING_STATE::WAIT_FOR_MQTT_CONNECT;
}

uint8_t UpdateLocalVariablesStateFn()
{
  //Wait time for the callback to be called
  if ((millis() - ulConnectionTimer) > 500)
    return RUNNING_STATE::POST_VARIABLES;

  return RUNNING_STATE::UPDATE_LOCAL_VARIABLES;
}

uint8_t PostVariablesStateFn()
{
  //Check if this device should be posting data
  if (!strcmp(sRemoteDeviceName, workingInfo.sDeviceName) || bBecomeRemoteDevice)
  {
    //These should block until completed
    if (bBecomeRemoteDevice)
      mqttClient.publish(workingInfo.sRemoteDevicePath, workingInfo.sDeviceName);

    mqttClient.publish(workingInfo.sAmbientTempPath, "");
    mqttClient.publish(workingInfo.sTargetTempPath, "");
    mqttClient.publish(workingInfo.sRequestedModePath, "");

    bBecomeRemoteDevice = false;
  }

  return RUNNING_STATE::SLEEP_START;
}

uint8_t StartSleepStateFn()
{
  return RUNNING_STATE::MQTT_DISCONNECT;
}

uint8_t MQTTDisconnectStateFn()
{
  mqttClient.disconnect();
  return RUNNING_STATE::WAIT_FOR_MQTT_DISCONNECT;
}

uint8_t WaitForMQTTDisconnectStateFn()
{
  //Disconnects automatically
  return RUNNING_STATE::TURN_WIFI_OFF;
}

uint8_t TurnWiFiOffStateFn()
{
  WiFi.mode(WIFI_OFF);
  ulConnectionTimer = millis();

  return RUNNING_STATE::WAIT_FOR_WIFI_OFF;
}

uint8_t WaitForWiFiOffStateFn()
{
  if (WiFi.getMode() == WIFI_OFF ||
      (millis() - ulConnectionTimer) > 250)
    return RUNNING_STATE::SLEEP;

  return RUNNING_STATE::WAIT_FOR_WIFI_OFF;
}

uint8_t SleepStateFn()
{
  //Skip sleeping if the charger is active
  if (aPinStatus[CHARGER_STS_PIN])
  {
    ulWakeTimeStart = millis();
    return RUNNING_STATE::SAMPLE;
  }

  //Sleep
  //Setup the reset latch
  digitalWrite(HB_LED_PIN, LOW); //Off
  digitalWrite(SLEEP_PIN, HIGH); //Before on
  //Turn off the battery status LED
  digitalWrite(BATT_LED_PIN, LOW);
  //Deep sleep
  ESP.deepSleep(ulSleepTime, WAKE_RF_DISABLED);

  //Wakeup
  //Clear the reset latch
  digitalWrite(SLEEP_PIN, LOW); //Off
  digitalWrite(HB_LED_PIN, HIGH); //Before on

  ulWakeTimeStart = millis();

  return RUNNING_STATE::SAMPLE;
}

std::map<uint8_t, std::function<uint8_t(void)>> runningStateFnMap =
{
  {RUNNING_STATE::SAMPLE, SampleStateFn},
  {RUNNING_STATE::TURN_WIFI_ON, WifiOnStateFn},
  {RUNNING_STATE::WAIT_FOR_WIFI_ON, WaitForWifiOnStateFn},
  {RUNNING_STATE::CONNECT_TO_NETWORK, ConnectToNetworkStateFn},
  {RUNNING_STATE::WAIT_FOR_NETWORK, WaitForNetworkStateFn},
  {RUNNING_STATE::MQTT_CONNECT, MQTTConnectStateFn},
  {RUNNING_STATE::WAIT_FOR_MQTT_CONNECT, WaitForMQTTConnectStateFn},
  {RUNNING_STATE::UPDATE_LOCAL_VARIABLES, UpdateLocalVariablesStateFn},
  {RUNNING_STATE::POST_VARIABLES, PostVariablesStateFn},
  {RUNNING_STATE::SLEEP_START, StartSleepStateFn},
  {RUNNING_STATE::MQTT_DISCONNECT, MQTTDisconnectStateFn},
  {RUNNING_STATE::WAIT_FOR_MQTT_DISCONNECT, WaitForMQTTDisconnectStateFn},
  {RUNNING_STATE::TURN_WIFI_OFF, TurnWiFiOffStateFn},
  {RUNNING_STATE::WAIT_FOR_WIFI_OFF, WaitForWiFiOffStateFn},
  {RUNNING_STATE::SLEEP, SleepStateFn}
};

void loop()
{
  if (runningStateFnMap.find(currentRunningState) != runningStateFnMap.end())
    currentRunningState = runningStateFnMap[currentRunningState]();
  else
    currentRunningState = RUNNING_STATE::SLEEP_START;

  mqttClient.loop();

  updateStatusLED();
  updateInputs();
}
