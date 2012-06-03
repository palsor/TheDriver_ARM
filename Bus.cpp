#include "Bus.h"

//
// constructor
//
Bus::Bus() {}

//
// init 
//
void Bus::init(HardwareSPI* spiPointer) {
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
  
  // initialize SPI
  spi = spiPointer;
  spi->begin(SPI_562_500KHZ, MSBFIRST, SPI_MODE_0);
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
bool Bus::i2cReadBuffer(uint8 i2cAddress, uint8 dataAddress, uint8 count, uint8* buffer) {
  bool returnValue = false;
  
  i2cWrite(i2cAddress, dataAddress);
  Wire.requestFrom(i2cAddress, count);    // request 6 bytes from device
  for (int i = 0; (i < count) && (Wire.available()); i++) {
    buffer[i] = Wire.receive();  
  }
  if (Wire.endTransmission() == SUCCESS)
    returnValue = true;

  return returnValue;
}

//
// spiRead
//
uint8 Bus::spiRead(uint8 dataAddress) {
  spi->transfer(dataAddress | 0x80);
  return spi->transfer(0);
}

//
// spiWrite
//
void Bus::spiWrite(uint8 dataAddress, uint8 data) {
  spi->transfer(dataAddress);
  spi->transfer(data);
}

//
// serial ports
//
unsigned int Bus::serialAvailable(uint8 bus) { return serialPorts[bus-1]->available(); }
unsigned char Bus::serialRead(uint8 bus) { return serialPorts[bus-1]->read(); }
void Bus::serialPrint(uint8 bus, const char* str) { serialPorts[bus-1]->print(str); }
void Bus::serialPrintln(uint8 bus, const char* str) { serialPorts[bus-1]->println(str); }
