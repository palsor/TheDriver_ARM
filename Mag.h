#ifndef MAG_H
#define MAG_H

#include "libmaple_types.h"

#include "Config.h"
#include "Externs.h"
#include "Bus.h"

#define MAG_I2C_ADDR      0x1E

#define REG_CRA_REG_M     0x00
#define REG_CRB_REG_M     0x01
#define REG_MR_REG_M      0x02
#define REG_OUT_X_H_M     0x03
#define REG_OUT_X_L_M     0x04
#define REG_OUT_Z_H_M     0x05
#define REG_OUT_Z_L_M     0x06
#define REG_OUT_Y_H_M     0x07
#define REG_OUT_Y_L_M     0x08
#define REG_SR_REG_M      0x09
#define REG_IR_REG1_M     0x0A
#define REG_IR_REG2_M     0x0B
#define REG_IR_REG3_M     0x0C
#define REG_TEMP_OUT_H_M  0x31
#define REG_TEMP_OUT_L_M  0x32

class Mag {
  public:
    Mag();
    void init();
    bool readRawValues(float* magValues);
    void calibrate(uint8 calRounds);
    
  private:
  
};

#endif
