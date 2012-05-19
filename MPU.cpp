#include "MPU.h"

//
// constructor
//
MPU::MPU() {}

// 
// init - setup the MPU
//
void MPU::init() {    
    
    // configure MPU registers
    bus.spiWrite(MPUREG_PWR_MGMT_1, BIT_H_RESET); // Chip reset
    delay(100);
    
    bus.spiWrite(MPUREG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ); // Wake up device and select GyroZ clock (better performance)
    bus.spiWrite(MPUREG_USER_CTRL, BIT_I2C_IF_DIS); // Disable I2C bus (recommended on datasheet)    
    bus.spiWrite(MPUREG_SMPLRT_DIV,19);     // Sample rate = 50Hz    Fsample= 1Khz/(19+1) = 50Hz     
    bus.spiWrite(MPUREG_CONFIG, BITS_DLPF_CFG_20HZ);  // FS & DLPF   FS=2000º/s, DLPF = 20Hz (low pass filter)
    bus.spiWrite(MPUREG_GYRO_CONFIG,BITS_FS_2000DPS);  // Gyro scale +/-2000º/s
    bus.spiWrite(MPUREG_ACCEL_CONFIG,0x08);            // Accel scale 4g (4096LSB/g)
    bus.spiWrite(MPUREG_INT_ENABLE,BIT_RAW_RDY_EN);         // INT: Raw data ready
    bus.spiWrite(MPUREG_INT_PIN_CFG,BIT_INT_ANYRD_2CLEAR);  // INT: Clear on any read
    
    // init values
    gyroCalibrationOffset[0] = 0;
    gyroCalibrationOffset[1] = 0;
    gyroCalibrationOffset[2] = 0;
}

//
// calibrate
//
void MPU::calibrate(int calRound) {
  // update calRound value, need 1-5 instead of 0-4;
  calRound++; 
  
  // calibrate gyros
  float gyroMpu[3];
  float accelMpu[3];
    
  if (readRawValues(gyroMpu, accelMpu, false)) {
    gyroCalibrationOffset[0] = gyroCalibrationOffset[0] * (1.0f - 1.0f/calRound) + gyroMpu[0] * 1.0f/calRound;
    gyroCalibrationOffset[1] = gyroCalibrationOffset[1] * (1.0f - 1.0f/calRound) + gyroMpu[1] * 1.0f/calRound;
    gyroCalibrationOffset[2] = gyroCalibrationOffset[2] * (1.0f - 1.0f/calRound) + gyroMpu[2] * 1.0f/calRound;
  }   
}

//
// readRawValues - reads values from the MPU, scales them, and converts the gryo to degrees
//
boolean MPU::readRawValues(float* gyro, float* accel, bool applyOffset) {
  boolean returnValue = false;
  
  if (bus.spiRead(MPUREG_INT_STATUS) & 0x01) {
    int byte_H;
    int byte_L;
  
    // Read AccelX
    byte_H = bus.spiRead(MPUREG_ACCEL_XOUT_H);
    byte_L = bus.spiRead(MPUREG_ACCEL_XOUT_L);
    accel[0] = (float)(((int)byte_H<<8)| byte_L) * ACCEL_X_SIGN;
    // Read AccelY
    byte_H = bus.spiRead(MPUREG_ACCEL_YOUT_H);
    byte_L = bus.spiRead(MPUREG_ACCEL_YOUT_L);
    accel[1] = (float)(((int)byte_H<<8)| byte_L) * ACCEL_Y_SIGN;
    // Read AccelZ
    byte_H = bus.spiRead(MPUREG_ACCEL_ZOUT_H);
    byte_L = bus.spiRead(MPUREG_ACCEL_ZOUT_L);
    accel[2] = (float)(((int)byte_H<<8)| byte_L) * ACCEL_Z_SIGN;
    
    // Read Temp
    // byte_H = spiRead(MPUREG_TEMP_OUT_H);
    // byte_L = spiRead(MPUREG_TEMP_OUT_L);
    // tempRaw = (byte_H<<8)| byte_L; 
     
    // Read GyroX
    byte_H = bus.spiRead(MPUREG_GYRO_XOUT_H);
    byte_L = bus.spiRead(MPUREG_GYRO_XOUT_L);
    gyro[0] = ((float)(((int)byte_H<<8) | byte_L)) * GYRO_X_SIGN / GYRO_SCALE;
  
    // Read GyroY
    byte_H = bus.spiRead(MPUREG_GYRO_YOUT_H);
    byte_L = bus.spiRead(MPUREG_GYRO_YOUT_L);
    gyro[1] = ((float)(((int)byte_H<<8) | byte_L)) * GYRO_Y_SIGN / GYRO_SCALE;
    // Read GyroZ
    byte_H = bus.spiRead(MPUREG_GYRO_ZOUT_H);
    byte_L = bus.spiRead(MPUREG_GYRO_ZOUT_L);
    gyro[2] = ((float)(((int)byte_H<<8) | byte_L)) * GYRO_Z_SIGN / GYRO_SCALE;
    
    if (applyOffset) {
      gyro[0] -= gyroCalibrationOffset[0];
      gyro[1] -= gyroCalibrationOffset[1];
      gyro[2] -= gyroCalibrationOffset[2];  
    }
    returnValue = true;
  }
  
  return(returnValue);
}

