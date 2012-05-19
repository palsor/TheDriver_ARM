#include "Compass.h"

//
// constructor
//
Compass::Compass() {}

//
// init - do any setup required
//
void Compass::init() { 
  // Set the compass to continuous mode
  uint8 buffer[2] = {MODE_REGISTER, CONTINUOUS_MODE};
  bus.i2cWriteBuffer(COMPASS_ADDRESS, 2, buffer); 
}

//
// update - read new data from the compass
//
bool Compass::readRawValues(float* mag) {
  bool returnValue = false;
  
  // read the compass values
  uint8 buffer[6];
  
  if (bus.i2cRead(COMPASS_ADDRESS, DATA_ADDRESS, 6, buffer))
    returnValue = true;

  // MSB byte first, then LSB, X,Y,Z
  mag[0] = (float)((((int)buffer[0]) << 8) | buffer[1]) * MAG_X_SIGN;    // X axis
  mag[1] = (float)((((int)buffer[4]) << 8) | buffer[5]) * MAG_Y_SIGN;    // Y axis
  mag[2] = (float)((((int)buffer[2]) << 8) | buffer[3]) * MAG_Z_SIGN;    // Z axis
  
  return returnValue;
}
