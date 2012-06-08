#include "Accel.h"

Accel::Accel() {}

void Accel::init() {
  bus.i2cWrite(ACCEL_I2C_ADDR, REG_CTRL_REG1_A, DATA_RATE_400KHZ);
  
}

bool Accel::readRawValues(float* accelValues) {
  return true;
}

void Accel::calibrate(uint8 calRounds) {
  
}
