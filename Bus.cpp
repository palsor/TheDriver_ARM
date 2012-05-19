#include "Bus.h"

//
// constructor
//
Bus::Bus() {}

//
// init 
//
void Bus::init() {
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
  Wire.begin(); // pins 20 and 21  
}

//
// i2cWriteBuffer
//
void Bus::i2cWriteBuffer(uint8 i2cAddress, uint8 count, uint8* buffer) {
  Wire.beginTransmission(i2cAddress);
  for (uint8 i = 0; i < count; i++) {
    Wire.send(*(buffer + i)); 
  }
  Wire.endTransmission(); 
}

//
// i2cWrite
//
void Bus::i2cWrite(uint8 i2cAddress, uint8 data) {
  Wire.beginTransmission(i2cAddress);
  Wire.send(data); 
  Wire.endTransmission();  
}

//
// i2cRead
//
void Bus::i2cRead(uint8 i2cAddress, uint8 dataAddress, uint8 count, uint8* buffer) {
  i2cWrite(i2cAddress, dataAddress);
  Wire.requestFrom(i2cAddress, count);    // request 6 bytes from device
  for (int i = 0; (i < count) && (Wire.available()); i++) {
    buffer[i] = Wire.receive();  
  }
  Wire.endTransmission();  
}

//
// spiRead
//
void Bus::spiRead(uint8 count, uint8* buffer) {
  
}

//
// serial ports
//
unsigned int Bus::serialAvailable(uint8 bus) { return serialPorts[bus-1]->available(); }
unsigned char Bus::serialRead(uint8 bus) { return serialPorts[bus-1]->read(); }
void Bus::serialPrint(uint8 bus, const char* str) { serialPorts[bus-1]->print(str); }
void Bus::serialPrintln(uint8 bus, const char* str) { serialPorts[bus-1]->println(str); }