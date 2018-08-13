//SoftDevice S130

#include <Arduino.h>
#include <BLEHIDPeripheral.h>
#include <BLEKeyboard.h>
#include "matrixHandler.h"

//#define ANDROID_CENTRAL

// create peripheral instance, see pinouts above
BLEHIDPeripheral bleHIDPeripheral = BLEHIDPeripheral();
BLEKeyboard bleKeyboard;

#define toHex(i) (((i) <= 9)?('0' +(i)):((i)+'@'-9))

MatrixHandler matrix;

void setup() {
  Serial.begin(9600);

  // clear bond store data
  bleHIDPeripheral.clearBondStoreData();

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

  matrix.begin();
  //matrix.show(matrix.YES);
  uint8_t img[] = {0b00110, 0b00101, 0b00110, 0b00101, 0b00110};
  matrix.show(img);

  //pinMode(0, OUTPUT);
  pinMode(5, INPUT);
}

void loop() {

  static unsigned long previousSerialMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - previousSerialMillis >= 1000) {
    previousSerialMillis = currentMillis;
    //digitalWrite(0, !digitalRead(0));
  }

  BLECentral central = bleHIDPeripheral.central();

  if (central) {
    // central connected to peripheral
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());

    while (central.connected()) {

      if (digitalRead(5) == LOW) {

        Serial.println("Press");
        //central.disconnect();
      }


      if (Serial.available() > 0) {
        // read in character
        char c = Serial.read();

        Serial.print(F("c = "));
        Serial.println(c);

        bleKeyboard.print(c);
      }
    }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
