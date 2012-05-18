#include "Servo.h"
#include "dma.h"

#include "Structs.h"
#include "Sensors.h"
#include "Controller.h"
#include "Communication.h"

// global data structs
SensorData sensorData;
CaptData captData;
NavData navData;
PilotData pilotData;
CommData commData;

// working objects
Sensors sensors;
//Captain captain;
//Navigator navigator;
//Pilot pilot;
Communication comms;
Controller controller;

void setup() {
  // init SPI bus - must come before sensor and comms init
  //SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV16);      // SPI at 1Mhz (on 16Mhz clock)
  //delay(10);
  
  //sensorData.airspeedRaw = 0;
  
  // init our objects
  //captain.init();
  //pilot.init();
  //navigator.init();
  sensors.init();
  comms.init();
  controller.init();  
  // setup interrupts - must occur after sensor init
  //attachInterrupt(0, mpuDataInt, RISING);

  // setup course waypoints
  //navigator.addWaypoint(30.359468,-97.904153); // Capella & Quinlan
  //navigator.addWaypoint(30.356086,-97.908718); // Quinlan & Bright Sky
  //navigator.addWaypoint(30.357274,-97.909227);  // brt sky & casseopia
  //navigator.addWaypoint(30.359007,-97.906118);  // casseopia & little dipper
  //navigator.addWaypoint(30.360123,-97.909407);  // little dipper brt sky

  //navigator.beginNavigation();
  
  // setup the serial port to the radio and the DMA controller
  RADIO_SERIAL.begin(RADIO_SERIAL_RATE);
  USART3->regs->CR3 = USART_CR3_DMAT;
  dma_init(DMA1); // void dma_init(dma_dev * dev)
} 

//
// loop - main program loop
//
void loop() {
  sensors.update();    // read from the sensors
  //captain.update();    // update state machine
  //navigator.update();  // update navigation calculations
  //pilot.update();      // update plane controls based on desired navigation
  controller.update();
  
  // setup data and init DMA to radio if ready for another transmission
  if (!commData.dmaInProgress) {
    comms.setupDataToSend(); 
    dma_setup_transfer(DMA1, DMA_CH2, &USART3->regs->DR, DMA_SIZE_8BITS, commData.bufferPointer, DMA_SIZE_8BITS, (DMA_MINC_MODE | DMA_FROM_MEM | DMA_TRNS_CMPLT)); // void dma_setup_transfer(dma_dev * dev, dma_channel channel, __io void * peripheral_address, dma_xfer_size peripheral_size, __io void * memory_address, dma_xfer_size memory_size, uint32 mode)
    dma_set_num_transfers(DMA1, DMA_CH2, commData.bufferLength); // void dma_set_num_transfers(dma_dev * dev, dma_channel channel, uint16 num_transfers)
    dma_attach_interrupt(DMA1, DMA_CH2, dma_irq); // void dma_attach_interrupt(dma_dev * dev, dma_channel channel, void(*)(void) handler)
    dma_enable(DMA1, DMA_CH2); // void dma_enable(dma_dev * dev, dma_channel channel)
    commData.dmaInProgress = true;
  }
}

//
// dma_irq - called when each DMA completes
//
void dma_irq() {
  commData.dmaInProgress = false;  
}
