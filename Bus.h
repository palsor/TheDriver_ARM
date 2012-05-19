#ifndef BUS_H
#define BUS_H

#include "libmaple_types.h"
#include "HardwareSerial.h"
#include "Wire.h"

#include "Config.h"

class Bus {
  public:
    Bus();
    void init();
    void i2cWriteBuffer(uint8 i2cAddress, uint8 count, uint8* buffer);
    void i2cWrite(uint8 i2cAddress, uint8 data);
    bool i2cRead(uint8 i2cAddress, uint8 dataAddress, uint8 count, uint8* buffer);
    void spiRead(uint8 count, uint8* buffer);
    
    unsigned int serialAvailable(uint8 bus);
    unsigned char serialRead(uint8 bus);
    void serialPrint(uint8 bus, const char* str);
    void serialPrintln(uint8 bus, const char* str);
    
  private:
    HardwareSerial* serialPorts[4];
    
};

#endif
