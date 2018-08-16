//SoftDevice S130

#include <Arduino.h>
#include <BLEHIDPeripheral.h>
#include <BLEKeyboard.h>
#include "matrixHandler.h"

//#define ANDROID_CENTRAL
//#define PIN2_OUTPUT

// create peripheral instance, see pinouts above
BLEHIDPeripheral bleHIDPeripheral = BLEHIDPeripheral();
BLEKeyboard bleKeyboard;

#define toHex(i) (((i) <= 9)?('0' +(i)):((i)+'@'-9))

MatrixHandler matrix;

unsigned char inputPins[5] = {0, 1, 2, 5, 11};
unsigned char keyCodes[5] = {KEYCODE_0, KEYCODE_1, KEYCODE_2, KEYCODE_A, KEYCODE_B};
bool buttonPressedRaw[5] = {false};
bool buttonPressedDebonced[5] = {false};
unsigned long previousKeyCheckMillis[5] = {0};

bool welcomeMessage = true;

void setup() {
  delay(100);

  Serial.begin(9600);

#ifdef ANDROID_CENTRAL
  bleHIDPeripheral.setReportIdOffset(1);
#endif

  ble_gap_addr_t gapAddress;
  sd_ble_gap_address_get(&gapAddress);

  char deviceName[] = "MBit UX 0000";
  uint32_t addressLow32bit = NRF_FICR->DEVICEADDR[0];
  for (int i = 0; i < 2; i++) {
    unsigned char addressByteChuck = (addressLow32bit >> ((1 - i) * 8)) & 0xFF;
    unsigned char d;
    d = addressByteChuck >> 4;
    deviceName[8 + i * 2 + 0] = toHex(d);
    d = addressByteChuck & 0x0f;
    deviceName[8 + i * 2 + 1] = toHex(d);
  }

  bleHIDPeripheral.setLocalName(deviceName);
  bleHIDPeripheral.setDeviceName(deviceName);
  bleHIDPeripheral.addHID(bleKeyboard);

  bleHIDPeripheral.begin();

  Serial.println();
  Serial.println(F("Experience Prototyping with IoT Devices"));
  Serial.println(F("UX Week 2018"));
  Serial.println(F("Deqing Sun & Peiqi Su"));

  Serial.print(F("Device Name: "));
  Serial.println(deviceName);

#ifdef ANDROID_CENTRAL
  Serial.println(F("Android Central"));
#endif

#ifdef PIN2_OUTPUT
  Serial.println(F("2 Input, 1 Ouput"));
#else
  Serial.println(F("3 Input"));
#endif

  matrix.begin();

  for (int i = 0; i < 5; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

#ifdef PIN2_OUTPUT
  pinMode(inputPins[2], OUTPUT);
#endif

}

void loop() {

  static unsigned long previousSerialMillis = 0;

  if (welcomeMessage) {
    if (millis() - previousSerialMillis >= 200) {  //
      static int scrollIndex = 32;
      previousSerialMillis = millis();
      matrix.scroll(matrix.UXWEEK, scrollIndex);
      scrollIndex--;
      if (scrollIndex < -5) welcomeMessage = false;
    }
  } else {
    if (millis() - previousSerialMillis >= 300) {  //show signal animation
      static int signalIndex = 0;
      previousSerialMillis = millis();
      matrix.show(matrix.SIGNAL[signalIndex]);
      signalIndex++;
      if (signalIndex >= 8) signalIndex = 0;
    }
  }

  //check whether AB is holddown at same time
  {
    static bool ABwasDown = false;
    static unsigned long ABDownTime;
    bool ABisDown = ((!digitalRead(5)) && (!digitalRead(11)));
    if (ABwasDown != ABisDown) {
      if (ABisDown) {
        Serial.println(F("AB both pressed"));
        ABDownTime = millis();
      }
      ABwasDown = ABisDown;
    } else if (ABisDown) { //holding
      if ((signed int)(millis() - ABDownTime) > 3000) {
        Serial.println(F("AB long hold"));
        // clear bond store data
        bleHIDPeripheral.clearBondStoreData();
        ABDownTime = millis();
        delay(100);
        NVIC_SystemReset();
      }
    }
  }


  BLECentral central = bleHIDPeripheral.central();

  if (central) {
    // central connected to peripheral
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());
    matrix.show(matrix.YES);

    while (central.connected()) {

      for (int i = 0; i < 5; i++) {
#ifdef PIN2_OUTPUT
        if (i == 2) continue; //don't use pin2 as input
#endif
        bool oneKeyPressed = !digitalRead(inputPins[i]);
        if (oneKeyPressed != buttonPressedRaw[i]) {
          previousKeyCheckMillis[i] = millis();
          buttonPressedRaw[i] = oneKeyPressed;
        }
        if (oneKeyPressed != buttonPressedDebonced[i]) {
          if ((signed long)(millis() - previousKeyCheckMillis[i]) > 50) {
            buttonPressedDebonced[i] = oneKeyPressed;
            Serial.print(F("Pin "));
            Serial.print(inputPins[i]);
            if (oneKeyPressed) {
              Serial.println(F(" pressed"));
              bleKeyboard.press(keyCodes[i], 0);
              matrix.setPixel(i, 4, 1);
            } else {
              Serial.println(F(" released"));
              bleKeyboard.release(keyCodes[i], 0);
              matrix.setPixel(i, 4, 0);
            }
          }
        }
      }

#ifdef PIN2_OUTPUT
      digitalWrite(2, buttonPressedDebonced[0] || buttonPressedDebonced[1]); //lit LED when 0 or 1 is connected.
#endif

      //check whether AB is holddown at same time
      {
        static bool ABwasDown = false;
        static unsigned long ABDownTime;
        bool ABisDown = (buttonPressedDebonced[3] && buttonPressedDebonced[4]);
        if (ABwasDown != ABisDown) {
          if (ABisDown) {
            Serial.println(F("AB both pressed"));
            ABDownTime = millis();
          }
          ABwasDown = ABisDown;
        } else if (ABisDown) { //holding
          if ((signed int)(millis() - ABDownTime) > 3000) {
            Serial.println(F("AB long hold"));
            bleKeyboard.releaseAll();
            central.disconnect();
            ABDownTime = millis();
            // clear bond store data
            bleHIDPeripheral.clearBondStoreData();
            delay(100);
            NVIC_SystemReset();
          }
        }
      }
    }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
