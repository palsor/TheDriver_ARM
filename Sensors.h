#ifndef SENSORS_H
#define SENSORS_H

#include "math.h"
#include "wirish_time.h"

#include "Config.h"
#include "Externs.h"
#include "Constants.h"
#include "GPS.h"
#include "MPU.h"
#include "Compass.h"
#include "Barometer.h"
#include "SingleWire.h"

class Sensors {
  public:
    Sensors();
    void init(GPS* gpsPointer, MPU* mpuPointer, Compass* compassPointer, Barometer* barometerPointer, SingleWire* singleWirePointer);
    void update();
    //void mpuDataInt();
    
   private:
     GPS* gps;
     Compass* compass;
     Barometer* barometer;
     SingleWire* singleWire;
     MPU* mpu;
     
     float rotation[3][3];
     unsigned long lastUpdateTime;
     
     void updateRotationMatrix(float* gyro, float* accel, float* mag);
     void eulerAngles();
     
     float matrixDot(float* a, float* b);
     void matrixRotate(float* bodyVec, float* earthVec);
     void matrixUnit(float* b);
     void matrixCross(float* a, float* b, float* c);
};

#endif
