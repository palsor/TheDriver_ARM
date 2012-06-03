#ifndef BAROMETER_H
#define BAROMETER_H

#include "wirish_time.h"
#include "libmaple_types.h"

#include "Config.h"
#include "Externs.h"
#include "Bus.h"

#define BAROMETER_ADDRESS 0x77

#define REG_CTRL 0xF4
#define REG_EEPROM_BEGIN 0xAA
#define REG_DATA 0xF6

#define CMD_START_TEMP 0x2E
#define CMD_START_PRESSURE 0x34

class Barometer {
  public:
    Barometer();
    void init();
    bool readRawValues(float* temp, float* pressure);
    
  private:
    short _AC1, _AC2, _AC3, _B1, _B2, _MB, _MC, _MD;
    unsigned short _AC4, _AC5, _AC6;
    long UT;
    uint8 state;
    unsigned long lastTime;
    
    unsigned short read16(uint8 address);
};

#endif
