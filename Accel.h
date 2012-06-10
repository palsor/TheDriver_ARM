#ifndef ACCEL_H
#define ACCEL_H

#include "libmaple_types.h"

#include "Config.h"
#include "Externs.h"
#include "Bus.h"

#define ACCEL_I2C_ADDR        0x19

#define REG_CTRL_REG1_A       0x20
#define REG_CTRL_REG2_A       0x21
#define REG_CTRL_REG3_A       0x22
#define REG_CTRL_REG4_A       0x23
#define REG_CTRL_REG5_A       0x24
#define REG_CTRL_REG6_A       0x25
#define REG_REF_DATACAPTURE_A 0x26
#define REG_STATUS_REG_A      0x27
#define REG_OUT_X_L_A         0x28
#define REG_OUT_X_H_A         0x29
#define REG_OUT_Y_L_A         0x2A
#define REG_OUT_Y_H_A         0x2B
#define REG_OUT_Z_L_A         0x2C
#define REG_OUT_Z_H_A         0x2D
#define REG_FIFO_CTRL_REG_A   0x2E
#define REG_FIFO_SRC_REG_A    0x2F
#define REG_INT1_CFG_A        0x30
#define REG_INT1_SRC_A        0x31
#define REG_INT1_THS_A        0x32
#define REG_INT1_DURATION_A   0x33
#define REG_INT2_CFG_A        0x34
#define REG_INT2_SRC_A        0x35
#define REG_INT2_THS_A        0x36
#define REG_INT2_DURATION_A   0x37
#define REG_TIME_LIMIT_A      0x3B
#define REG_TIME_LATENCY_A    0x3C
#define REG_TIME_WINDOW_A     0x3D

#define MASK_DATA_RATE        0x0F << 4
#define VAL_DATA_RATE_100HZ   0x05 << 4
#define VAL_DATA_RATE_200HZ   0x06 << 4
#define VAL_DATA_RATE_400HZ   0x07 << 4
#define VAL_DATA_RATE_1344HZ  0x09 << 4

#define MASK_POWER_MODE       0x01 << 3
#define VAL_POWER_MODE_NORMAL 0x00 << 3
#define VAL_POWER_MODE_LOW    0x01 << 3

#define MASK_AXIS_ENABLE      0x07
#define VAL_ALL_AXIS_ENABLE   0x07

#define MASK_FULL_SCALE       0x03 << 4
#define VAL_FULL_SCALE_2G     0x00 << 4
#define VAL_FULL_SCALE_4G     0x01 << 4
#define VAL_FULL_SCALE_8G     0x02 << 4
#define VAL_FULL_SCALE_16G    0x03 << 4

#define MASK_HIGH_RES_MODE    0x01 << 3
#define VAL_NORMAL_RES_MODE   0x00 << 3
#define VAL_HIGH_RES_MODE     0x01 << 3

#define MASK_NEW_DATA         0x01 << 3

#define MASK_FIFO_MODE        0x03 << 6
#define VAL_FIFO_MODE_BYPASS  0x00 << 6
#define VAL_FIFO_MODE_FIFO    0x01 << 6
#define VAL_FIFO_MODE_STREAM  0x02 << 6
#define VAL_FIFO_MODE_TRIGGER 0x03 << 6

class Accel {
  public:
    Accel();
    void init();
    bool readRawValues(float* accelValues);
    void calibrate(uint8 calRounds);
    
  private:
  
};

#endif
