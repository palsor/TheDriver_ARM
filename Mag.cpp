#include "Mag.h"

Mag::Mag() {}

void Mag::init() {
  bus.i2cWrite(MAG_I2C_ADDR, REG_CRA_REG_M, VAL_DATA_RATE_220HZ, MASK_DATA_RATE); // set output data rate (turn device on)
  bus.i2cWrite(MAG_I2C_ADDR, REG_MR_REG_M, VAL_CONV_MODE_CONT, MASK_CONV_MODE); // set mag mode
  bus.i2cWrite(MAG_I2C_ADDR, REG_CRB_REG_M, VAL_GAIN_13G, MASK_GAIN); // set gain
}

bool Mag::readRawValues(float* magValues) {
  uint8 temp[2];
  
  // read X values
  bus.i2cRead(MAG_I2C_ADDR, REG_OUT_X_H_M, 2, temp);
  magValues[0] = (temp[0] << 8) | temp[1];
  // read Y values
  bus.i2cRead(MAG_I2C_ADDR, REG_OUT_Y_H_M, 2, temp);
  magValues[1] = (temp[0] << 8) | temp[1];
  // read Z values
  bus.i2cRead(MAG_I2C_ADDR, REG_OUT_H_M, 2, temp);
  magValues[2] = (temp[0] << 8) | temp[1];
  
  return true;
}

void Mag::calibrate(uint8 calRounds) {
  
}
