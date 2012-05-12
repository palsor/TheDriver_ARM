#ifndef SENSORS_H
#define SENSORS_H

//#include <Arduino.h>
#include <math.h>
#include <wirish_time.h>

#include "Config.h"
#include "Externs.h"
#include "Constants.h"

//#include "Compass.h"
//#include "MPU6000.h"
//#include "GPS.h"
//#include "Barometer.h"
//#include "SingleWire.h"

class Sensors {
  public:
    Sensors();
    void init();
    void update();
    //void mpuDataInt();
    
   private:
     //Compass compass;
     //GPS gps;
     //MPU6000 mpu;
     //Barometer barometer;
     //SingleWire singleWire;
     
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
