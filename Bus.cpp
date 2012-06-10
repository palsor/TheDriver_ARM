#include "Bus.h"

//
// constructor
//
Bus::Bus() {}

//
// init 
//
void Bus::init(HardWire* i2cPointer) {
  // initialize serial ports
  serialPorts[0] = &Serial1;
  serialPorts[1] = &Serial2;
  serialPorts[2] = &Serial3;

  serialPorts[RADIO_SERIAL_PORT-1]->begin(RADIO_SERIAL_RATE);
  serialPorts[RADIO_SERIAL_PORT-1]->flush();
  USART3->regs->CR3 = USART_CR3_DMAT;
  
  serialPorts[GPS_SERIAL_PORT-1]->begin(GPS_SERIAL_RATE);
  serialPorts[RADIO_SERIAL_PORT-1]->flush();

  // initialize i2c
  i2c = i2cPointer;
  i2c->begin();  
}

//
// i2cWrite
//
void Bus::i2cWrite(uint8 i2cAddress, uint8 regAddress, uint8 data) {
  i2c->beginTransmission(i2cAddress);
  i2c->send(regAddress);
  i2c->send(data); 
  i2c->endTransmission();  
}

//
// i2cWrite
//
void Bus::i2cWrite(uint8 i2cAddress, uint8 regAddress, uint8 data, uint8 bitmask) {
  uint8 temp;
  i2cRead(i2cAddress, regAddress, 1, &temp);
  bitmask ^= 0xFF; // invert the bitmask with an xor
  temp &= bitmask; // mask off the data from the register
  temp |= data; // write the new data
  i2cWrite(i2cAddress, regAddress, temp);
}

//
// i2cRead
//
bool Bus::i2cRead(uint8 i2cAddress, uint8 regAddress, uint8 count, uint8* buffer) {
  bool returnValue = false;
  
  i2c->beginTransmission(i2cAddress);
  i2c->send(regAddress);
  i2c->endTransmission();
  i2c->requestFrom(i2cAddress, count);    // request 6 bytes from device
  for (int i = 0; (i < count) && (i2c->available()); i++) {
    buffer[i] = i2c->receive();  
  }
  if (i2c->endTransmission() == SUCCESS)
    returnValue = true;

  return returnValue;
}

//
// serial ports
//
unsigned int Bus::serialAvailable(uint8 bus) { return serialPorts[bus-1]->available(); }
unsigned char Bus::serialRead(uint8 bus) { return serialPorts[bus-1]->read(); }
void Bus::serialPrint(uint8 bus, const char* str) { serialPorts[bus-1]->print(str); }
void Bus::serialPrintln(uint8 bus, const char* str) { serialPorts[bus-1]->println(str); }
