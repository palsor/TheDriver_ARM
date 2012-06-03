#ifndef BUS_H
#define BUS_H

#include "libmaple_types.h"
#include "HardwareSerial.h"
#include "HardwareSPI.h"
#include "Wire.h"

#include "Config.h"

class Bus {
  public:
    Bus();
    void init(HardwareSPI* spiPointer);
    void i2cWriteBuffer(uint8 i2cAddress, uint8 count, uint8* buffer);
    void i2cWrite(uint8 i2cAddress, uint8 data);
    bool i2cReadBuffer(uint8 i2cAddress, uint8 dataAddress, uint8 count, uint8* buffer);
    uint8 spiRead(uint8 dataAddress);
    void spiWrite(uint8 dataAddress, uint8 data);
    
    unsigned int serialAvailable(uint8 bus);
    unsigned char serialRead(uint8 bus);
    void serialPrint(uint8 bus, const char* str);
    void serialPrintln(uint8 bus, const char* str);
    
  private:
    HardwareSerial* serialPorts[4];
    HardwareSPI* spi;
    
};

#endif
