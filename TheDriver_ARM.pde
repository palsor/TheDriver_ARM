#include "Structs.h"
#include "Sensors.h"

// global data structs
SensorData sensorData;
CaptData captData;
NavData navData;
PilotData pilotData;

// working objects
Sensors sensors;
//Captain captain;
//Navigator navigator;
//Pilot pilot;
//Communication comms;

void setup() {
  
  // init feedback LED pins
  //pinMode(RED_LED,OUTPUT);
  //digitalWrite(RED_LED, LOW);
  //pinMode(BLUE_LED,OUTPUT);
  //digitalWrite(BLUE_LED,HIGH);
  
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
  //comms.init();
  
  // setup interrupts - must occur after sensor init
  //attachInterrupt(0, mpuDataInt, RISING);

  // setup course waypoints
  //navigator.addWaypoint(30.359468,-97.904153); // Capella & Quinlan
  //navigator.addWaypoint(30.356086,-97.908718); // Quinlan & Bright Sky
  //navigator.addWaypoint(30.357274,-97.909227);  // brt sky & casseopia
  //navigator.addWaypoint(30.359007,-97.906118);  // casseopia & little dipper
  //navigator.addWaypoint(30.360123,-97.909407);  // little dipper brt sky

  //navigator.beginNavigation();

} 

void loop() {
  sensors.update();    // read from the sensors
  //captain.update();    // update state machine
  //navigator.update();  // update navigation calculations
  //pilot.update();      // update plane controls based on desired navigation
  //comms.sendData();    // send data to arduino mini
}
