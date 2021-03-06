#ifndef SENSORS_H
#define SENSORS_H

#include "math.h"
#include "wirish_time.h"

#include "Config.h"
#include "Externs.h"
#include "Constants.h"
#include "GPS.h"
#include "Mag.h"
#include "Accel.h"
#include "Gyro.h"
#include "Barometer.h"
#include "SingleWire.h"

class Sensors {
  public:
    Sensors();
    void init(GPS* gpsPointer, Mag* magPointer, Accel* accelPointer, Gyro* gyroPointer, Barometer* barometerPointer, SingleWire* singleWirePointer);
    void update();
    //void mpuDataInt();
    
   private:
     GPS* gps;
     Barometer* barometer;
     SingleWire* singleWire;
     Mag* mag;
     Accel* accel;
     Gyro* gyro;
     
     float rotation[3][3];
     unsigned long lastUpdateTime;
     
     void updateRotationMatrix(float* gyroValues, float* accelValues, float* magValues);
     void eulerAngles();
     
     float matrixDot(float* a, float* b);
     void matrixRotate(float* bodyVec, float* earthVec);
     void matrixUnit(float* b);
     void matrixCross(float* a, float* b, float* c);
};

#endif
