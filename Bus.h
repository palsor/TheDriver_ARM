#ifndef BUS_H
#define BUS_H

#include "libmaple_types.h"
#include "HardwareSerial.h"
#include "HardwareSPI.h"
#include "HardWire.h"

#include "Config.h"

class Bus {
  public:
    Bus();
    void init(HardWire* i2cPointer, HardwareSPI* spiPointer);
    void i2cWrite(uint8 i2cAddress, uint8 regAddress, uint8 data);
    bool i2cRead(uint8 i2cAddress, uint8 regAddress, uint8 count, uint8* buffer);
    uint8 spiRead(uint8 regAddress);
    void spiWrite(uint8 regAddress, uint8 data);
    
    unsigned int serialAvailable(uint8 bus);
    unsigned char serialRead(uint8 bus);
    void serialPrint(uint8 bus, const char* str);
    void serialPrintln(uint8 bus, const char* str);
    
  private:
    HardwareSerial* serialPorts[4];
    HardWire* i2c;
    HardwareSPI* spi;  
};

#endif
