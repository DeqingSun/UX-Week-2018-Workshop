#include "mbSensor.h"

MBSensor::MBSensor() {
  microbitSensorVersion = 0;
  accelInitialized = false;
}


uint8_t MBSensor::init() {
  microbitSensorVersion = 0;
  Wire.begin();
  byte error;
  if (microbitSensorVersion == 0) {
    Wire.beginTransmission(0x1D); //v1.3 MMA_8653_DEFAULT_ADDRESS
    error = Wire.endTransmission();
    if (error == 0) {
      microbitSensorVersion = 13;
      Serial.println(F("MMA8653 found on ver MicroBit v1.3"));
      _addr = 0x1D;
      accelInitialized = initMMA8653();
    }
  }
  if (microbitSensorVersion == 0) {
    Wire.beginTransmission(0x19); //v1.5 LSM303AGR_ACC_I2C_ADDRESS
    error = Wire.endTransmission();
    if (error == 0) {
      microbitSensorVersion = 15;
      Serial.println(F("LSM303AGR found on ver MicroBit v1.5"));
      _addr = 0x19;
      accelInitialized = initLSM303();
    }
  }


}

uint8_t MBSensor::initLSM303() {
  if (_read_register(LSM303_WHO_AM_I_A) != LSM303_A_WHOAMI_VAL) return 0;

  _write_register(LSM303_CTRL_REG1_A, 0b01110111);  //400Hz, XYZ enable
  _write_register(LSM303_CTRL_REG4_A, 0b10010000);  //Block data update, 4G range

  return 1;
}

uint8_t MBSensor::initMMA8653() {
  if (_read_register(MMA8653_WHOAMI) != MMA8653_WHOAMI_VAL) return 0;

  // First place the device into standby mode, so it can be configured.
  _write_register(MMA8653_CTRL_REG1, 0x00);

  // Enable high precisiosn mode. This consumes a bit more power, but still only 184 uA!
  _write_register(MMA8653_CTRL_REG2, 0x10);

  // Configure for the selected 4g range.
  _write_register(MMA8653_XYZ_DATA_CFG, 0x01);

  // Bring the device back online, with 10bit wide samples at the requested frequency 400hz.
  _write_register(MMA8653_CTRL_REG1, 0b00001000 | 0x01);

  return 1;
}


uint8_t MBSensor::readSensor() {
  if (accelInitialized) {
    if (microbitSensorVersion == 15) {
      _read_register_multiple(LSM303_OUT_X_L_A | 0x80, 6, dataBuf);

      accX = (int16_t)(dataBuf[1] << 8 | dataBuf[0]);  //left-justified, 32768=4G, 8192=1G
      accY = (int16_t)(dataBuf[3] << 8 | dataBuf[2]);
      accZ = (int16_t)(dataBuf[5] << 8 | dataBuf[4]);
    } else if (microbitSensorVersion == 13) {
      _read_register_multiple(MMA8653_OUT_X_MSB, 6, dataBuf);

      accX = (int16_t)(dataBuf[0] << 8 | dataBuf[1]);  //left-justified, 32768=4G, 8192=1G
      accY = (int16_t)(dataBuf[2] << 8 | dataBuf[3]);
      accZ = (int16_t)(dataBuf[4] << 8 | dataBuf[5]);
    }
  } else {
    return 0;
  }
}


uint8_t MBSensor::_read_register(uint8_t offset) {
  Wire.beginTransmission(_addr);
  Wire.write(offset);
  Wire.endTransmission(false);

  Wire.requestFrom(_addr, (uint8_t)1);
  if (Wire.available()) return Wire.read();
  return 0;
}

uint8_t MBSensor::_read_register_multiple(uint8_t offset, uint8_t len, uint8_t *readBuf) {
  Wire.beginTransmission(_addr);
  Wire.write(offset);
  Wire.endTransmission(false);
  Wire.requestFrom(_addr, len);
  uint8_t i = 0;
  for (; i < len; i++) {
    if (Wire.available()) {
      readBuf[i] = Wire.read();
    } else {
      break;
    }
  }
  return i;
}

void MBSensor::_write_register(uint8_t offset, uint8_t b) {
  Wire.beginTransmission(_addr);
  Wire.write(offset);
  Wire.write(b);
  Wire.endTransmission();
}
