#include "Sensors.h"

//
// constructor
//
Sensors::Sensors() {}

//
// init
//
void Sensors::init(GPS* gpsPointer, Mag *magPointer, Accel* accelPointer, Gyro* gyroPointer, Barometer* barometerPointer, SingleWire* singleWirePointer) {
  
  gps = gpsPointer;
  mag = magPointer;
  accel = accelPointer;
  gyro = gyroPointer;
  barometer = barometerPointer;
  singleWire = singleWirePointer;
  gps->init();
  mag->init();
  accel->init();
  gyro->init();
  barometer->init();
  singleWire->init();
  
  // calibrate any sensors that need calibration
  for (int i = 0; i < CALIBRATION_ROUNDS; i++) {
    delay(1000);
    mag->calibrate(i);
    accel->calibrate(i);
    gyro->calibrate(i);
    singleWire->calibrate(i);
  }
  
  // init variables
  lastUpdateTime = micros();
  
  // generate initial rotation matrix
  float gyroValues[3];
  float accelValues[3];
  float magValues[3];
  boolean gotValues = false;
  
  do {
    delay(200);    
    if (mag->readRawValues(magValues) && accel->readRawValues(accelValues) && gyro->readRawValues(gyroValues)) {
      for (int i = 0; i++; i < 3) {
        sensorData.gyro_b[i] = gyroValues[i];  
      }
      
      // convert accels and mag to unit vectors
      matrixUnit(accelValues);
      matrixUnit(magValues);
      
      // we want the positive K vector, so invert gravity
      accelValues[0] = -accelValues[0];
      accelValues[1] = -accelValues[1];
      accelValues[2] = -accelValues[2];
      
      // adjust mag to account for downward component of earth's magnetic field
      float scalar = matrixDot(magValues, accelValues);
      for (int i = 0; i < 3; i++) {
        magValues[i] -= scalar * accelValues[i];  
      }
      matrixUnit(magValues);
      
      // calculate K x I = J
      float j[3];
      matrixCross(accelValues, magValues, j);
      
      rotation[0][0] = magValues[0];
      rotation[0][1] = magValues[1];
      rotation[0][2] = magValues[2];
      
      rotation[1][0] = j[0];
      rotation[1][1] = j[1];
      rotation[1][2] = j[2];
      
      rotation[2][0] = accelValues[0];
      rotation[2][1] = accelValues[1];
      rotation[2][2] = accelValues[2];
    
      gotValues = true;
    }  
  } while (gotValues == false);
}

//
// update - gets latest data from sensors if it is time to read them again
//
void Sensors::update() {
  
  // gps
  gps->update();

  // barometer
  float temp, pressure;
  if (barometer->readRawValues(&temp, &pressure)) {
    // calculate altitude
    sensorData.pressAltitude = 44330 * (1.0 - pow(pressure / PRESSURE_SEA_LEVEL, 0.1903));
  }
    
  // mag/accel/gyro
  float gyroValues[3], accelValues[3], magValues[3];
  if (mag->readRawValues(magValues) && accel->readRawValues(accelValues) && gyro->readRawValues(gyroValues)) {
    for (int i = 0; i++; i < 3) {
      sensorData.gyro_b[i] = gyroValues[i];  
    }
    
    updateRotationMatrix(gyroValues, accelValues, magValues);
    eulerAngles();
  }

  // airspeed
  float airspeedBody[3] = {singleWire->readAirspeed(), 0, 0};
  sensorData.airspeedRaw = airspeedBody[0];
  matrixRotate(airspeedBody, sensorData.airspeed_e); 
}

//
// updateRotationMatrix - read the accel/mag/gyro, calculate the change in the angle, and update the rotation matrix
//
void Sensors::updateRotationMatrix(float* gyroValues, float* accelValues, float* magValues) {
      
  //
  // calculate angular change from gyros
  //
      
  // figure out how long it's been since our last update
  unsigned long curTime = micros();
  float timeDelta = curTime - lastUpdateTime;
  lastUpdateTime = curTime;
      
  // calculate angular change from gyro values
  for (int i = 0; i < 3; i++) {
    gyroValues[i] *= timeDelta / 1000000.0f * DEG2RAD; 
  } 
    
  //
  // calculate angular change from each of mag and accel
  //
    
  // convert mag and accel to unit vectors
  matrixUnit(magValues); 
  matrixUnit(accelValues); 
    
  // invert accel so gravity is correctly pointing down
  for (int i = 0; i < 3; i++) {
    accelValues[i] = -1.0f * accelValues[i];
  }
  
  // adjust mag to account for downward component of earth's magnetic field
  float scalar = matrixDot(magValues, accelValues);
  for (int i = 0; i < 3; i++) {
    magValues[i] -= scalar * accelValues[i];  
  }
  matrixUnit(magValues);
    
  // calculate angular change from mag and accel
  for (int i = 0; i < 3; i++) {
    magValues[i] = magValues[i] - rotation[0][i];       
    accelValues[i] = accelValues[i] - rotation[2][i];
  }
      
  float magAngle[3];
  matrixCross(rotation[0], magValues, magAngle);
  float accelAngle[3];
  matrixCross(rotation[2], accelValues, accelAngle);
    
  //
  // weight gyros, mag, and accel to calculate final answer
  //
  float finalAngle[3];
  for (int i = 0; i < 3; i++) {
    finalAngle[i] = gyroValues[i] * GYRO_WEIGHT + magAngle[i] * MAG_WEIGHT + accelAngle[i] * ACCEL_WEIGHT;  
  }
     
  //
  // update rotation matrix with new values
  //
    
  // calculate new vectors
  float I[3], K[3];
  matrixCross(finalAngle, rotation[0], I);
  matrixCross(finalAngle, rotation[2], K);
    
  // update the rotation matrix
  for (int i = 0; i < 3; i++) {
    rotation[0][i] += I[i];
    rotation[2][i] += K[i];    
  }
    
  //
  // check that the rotation matrix vectors are still perpendicular and unit length
  //
  float error = matrixDot(rotation[0], rotation[2]) / 2;
  float temp[3] = {rotation[0][0], rotation[0][1], rotation[0][2]};
    
  for (int i = 0; i < 3; i++) {
    rotation[0][i] = rotation[0][i] - error * rotation[2][i];
    rotation[2][i] = rotation[2][i] - error * temp[i];  
  }
    
  matrixUnit(rotation[0]);
  matrixUnit(rotation[2]);
      
  //
  // calculate the J vector and fill in the last row of the rotation matrix
  //
  matrixCross(rotation[2], rotation[0], rotation[1]);
}

//
// eulerAngles - calculates new euler angles from the rotation matrix
//
void Sensors::eulerAngles() {
  // calulate updated Euler angles
  sensorData.pitch_e = asin(rotation[2][0]);
  sensorData.yaw_e = atan2(rotation[1][0]/cos(sensorData.pitch_e), rotation[0][0]/cos(sensorData.pitch_e)) * RAD2DEG;
  sensorData.roll_e = -atan2(rotation[2][1]/cos(sensorData.pitch_e), rotation[2][2]/cos(sensorData.pitch_e)) * RAD2DEG;
    
  // fixup euler angles
  sensorData.pitch_e = sensorData.pitch_e * RAD2DEG;
    
  if (sensorData.yaw_e < 0)
    sensorData.yaw_e += 360;
      
  if (sensorData.roll_e < 0)
    sensorData.roll_e += 360;   
}

/*void Sensors::mpuDataInt() {
  mpu.dataInt();  
}*/

//
// matrixDot - returns the dot product of a . b
//
float Sensors::matrixDot(float* a, float* b) {
  float returnValue = 0;
  
  for (int i = 0; i < 3; i++) {
    returnValue += a[i] * b[i];
  }  
  return(returnValue);
}

//
// matrixUnit - takes vector a and converts it into a unit vector
//
void Sensors::matrixUnit(float* a) {
  float magnitude = 0;
 
  for (int i = 0; i < 3; i++) {
    magnitude += a[i] * a[i];  
  } 
  
  magnitude = sqrt(magnitude);
  
  for (int i = 0; i < 3; i++) {
    a[i] = a[i] / magnitude;  
  } 
}

//
// matrixCross - calculate the cross product of a x b = c
//
void Sensors::matrixCross(float* a, float* b, float* c) {
  c[0] = a[1] * b[2] - a[2] * b[1];
  c[1] = a[2] * b[0] - a[0] * b[2];
  c[2] = a[0] * b[1] - a[1] * b[0];
} 

void Sensors::matrixRotate(float* bodyVec, float* earthVec) {
  for (int i = 0; i < 3; i++) {
    earthVec[i] = rotation[i][0] * bodyVec[0] + rotation[i][1] * bodyVec[1] + rotation[i][2] * bodyVec[2];
  }  
}
