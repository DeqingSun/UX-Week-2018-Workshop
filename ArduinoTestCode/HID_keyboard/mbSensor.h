#ifndef _MB_SENSOR_H_
#define _MB_SENSOR_H_
#include <Arduino.h>
#include "Wire.h"

class MBSensor {
  public:
    MBSensor();
    uint8_t init();
    uint8_t readSensor();

    uint8_t initLSM303();
    uint8_t initMMA8653();

    uint8_t _read_register(uint8_t offset);
    uint8_t _read_register_multiple(uint8_t offset, uint8_t len, uint8_t *readBuf);
    void _write_register(uint8_t offset, uint8_t b);

    uint8_t dataBuf[6];

    

    bool accelInitialized;
    uint8_t _addr;
    uint8_t microbitSensorVersion;
    int16_t accX,accY,accZ;
};



#define LSM303_STATUS_REG_AUX_A        0x07
#define LSM303_OUT_TEMP_L_A           0x0C
#define LSM303_OUT_TEMP_H_A           0x0D
#define LSM303_INT_COUNTER_REG_A    0x0E
#define LSM303_WHO_AM_I_A           0x0F
#define LSM303_TEMP_CFG_REG_A       0x1F
#define LSM303_CTRL_REG1_A            0x20
#define LSM303_CTRL_REG2_A            0x21
#define LSM303_CTRL_REG3_A            0x22
#define LSM303_CTRL_REG4_A            0x23
#define LSM303_CTRL_REG5_A            0x24
#define LSM303_CTRL_REG6_A            0x25
#define LSM303_DATACAPTURE_A        0x26
#define LSM303_STATUS_REG_A           0x27
#define LSM303_OUT_X_L_A            0x28
#define LSM303_OUT_X_H_A            0x29
#define LSM303_OUT_Y_L_A            0x2A
#define LSM303_OUT_Y_H_A            0x2B
#define LSM303_OUT_Z_L_A            0x2C
#define LSM303_OUT_Z_H_A            0x2D
#define LSM303_FIFO_CTRL_REG_A        0x2E
#define LSM303_FIFO_SRC_REG_A       0x2F
#define LSM303_INT1_CFG_A           0x30
#define LSM303_INT1_SRC_A           0x31
#define LSM303_INT1_THS_A           0x32
#define LSM303_INT1_DURATION_A        0x33
#define LSM303_INT2_CFG_A           0x34
#define LSM303_INT2_SRC_A           0x35
#define LSM303_INT2_THS_A           0x36
#define LSM303_INT2_DURATION_A        0x37
#define LSM303_CLICK_CFG_A            0x38
#define LSM303_CLICK_SRC_A            0x39
#define LSM303_CLICK_THS_A            0x3A
#define LSM303_TIME_LIMIT_A           0x3B
#define LSM303_TIME_LATENCY_A       0x3C
#define LSM303_TIME_WINDOW_A        0x3D
#define LSM303_ACT_THS_A            0x3E
#define LSM303_ACT_DUR_A            0x3F

/**
    LSM303_A constants
*/
#define LSM303_A_WHOAMI_VAL             0x33



#define MMA8653_STATUS          0x00
#define MMA8653_OUT_X_MSB       0x01
#define MMA8653_WHOAMI          0x0D
#define MMA8653_XYZ_DATA_CFG    0x0E
#define MMA8653_CTRL_REG1       0x2A
#define MMA8653_CTRL_REG2       0x2B
#define MMA8653_CTRL_REG3       0x2C
#define MMA8653_CTRL_REG4       0x2D
#define MMA8653_CTRL_REG5       0x2E


/**
  * MMA8653 constants
  */
#define MMA8653_WHOAMI_VAL      0x5A
#endif
