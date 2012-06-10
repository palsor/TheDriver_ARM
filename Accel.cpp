#include "Accel.h"

Accel::Accel() {}

void Accel::init() {
  bus.i2cWrite(ACCEL_I2C_ADDR, REG_CTRL_REG1_A, VAL_DATA_RATE_400HZ, MASK_DATA_RATE); // set output data rate (turn device on)
  bus.i2cWrite(ACCEL_I2C_ADDR, REG_CTRL_REG1_A, VAL_POWER_MODE_NORMAL, MASK_POWER_MODE); // set power mode
  bus.i2cWrite(ACCEL_I2C_ADDR, REG_CTRL_REG4_A, VAL_HIGH_RES_MODE, MASK_HIGH_RES_MODE); // set high res mode
  bus.i2cWrite(ACCEL_I2C_ADDR, REG_CTRL_REG4_A, VAL_FULL_SCALE_8G, MASK_FULL_SCALE); // set full scale
}

bool Accel::readRawValues(float* accelValues) {
  uint8 temp[2];
  
  // read X values
  bus.i2cRead(ACCEL_I2C_ADDR, REG_OUT_X_L_A, 2, temp);
  accelValues[0] = (temp[1] << 8) | temp[0];
  // read Y values
  bus.i2cRead(ACCEL_I2C_ADDR, REG_OUT_Y_L_A, 2, temp);
  accelValues[1] = (temp[1] << 8) | temp[0];
  // read Z values
  bus.i2cRead(ACCEL_I2C_ADDR, REG_OUT_Z_L_A, 2, temp);
  accelValues[2] = (temp[1] << 8) | temp[0];
  
  return true;
}

void Accel::calibrate(uint8 calRounds) {
  
}
