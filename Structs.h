#ifndef STRUCTS_H
#define STRUCTS_H

#include "libmaple_types.h"

struct Waypoint {  // W
  float latitude;  // lat:10
  float longitude;  // lon:10
};

struct Vector {  // V
  float direction;  // dir
  float magnitude;  // mag:2
};

struct SensorData {  
  float gpsBearing;     // Gb degrees
  float gpsSpeed;       // Gs m/s       
  Waypoint curLocation; // cl lat/long in degrees
  float gpsHDOP;        // Gerr decimal
  float gpsAltitude;    // Galt meters
  float pitch_e;        // P degrees in earth's frame of reference
  float yaw_e;          // Y degrees in earth's frame of reference
  float roll_e;         // R degrees in earth's frame of reference
  float pressAltitude;  // Palt meters
  float airspeedRaw;    // AS magnitude
  float airspeed_e[3];  // AS m/s in earth's frame of reference
  float gyro_b[3];      // rotation about each axis in body's frame of reference
  float battVoltage;    // V volts
  bool gpsUpdated;      // Gu 1 = GPS data was updated, 0 = GPS was not updated
  unsigned char radioMuxSelect;  // Mx 1 = radio, 0 = autopilot
  unsigned char gpsSatellites;   // G# number of satellites
  unsigned char gpsFixType;      // Gfx 1 = no fix, 2 = 2D, 3 = 3D
};

struct CaptData {
  int curState;  // CSt current state of navigation state machine
  int prevState;  // Pst previous state of navigation state machine
  unsigned long lastStateTransitionTime;  // Tlu last navigator state transition time
};

struct NavData {
  int maxValidCourseIdx;  // MCidx max valid index of waypoints & courseDistances    
  unsigned long lastUpdateTime;  // Tlu last navigator update loop time
  Waypoint estLocation;  // el estimated location updated between GPS fixes
  Vector curDistance;  // cd calculated distance/bearing to next waypoint
  Vector estDistance;  // ed estimated distance since last loop iteration (NOT to next waypoint)
  Vector curGroundSpeed;  // cgs created from gpsSpeed/gpsBearing
  Vector estGroundSpeed;  // egs created from curAirSpeed+curWindSpeed
  Vector curAirSpeed;  // cas created from airspeed/magBearing
  Vector curWindSpeed;  // cws calculated from curGroundSpeed - curAirSpeed
  Vector targetAirSpeed;  // tas calculated desired heading in plane reference with normalized speed
};

struct PilotData {
  float throttleValue;  // Thr throttle value sent to controller (0-99%)
  float elevatorAngle;  // Elv itch value sent to controller (0-360 degrees)
  float rudderAngle;  // Rud yaw value sent to controller (0-360 degrees)
  float aileronAngle;  // Ail roll value sent to controller (0-360 degrees)
};

struct CommData {
  int bufferLength;
  uint8* bufferPointer;
  bool dmaInProgress;
};

struct ErrorData {
  bool compassReadError;  // Rderr
  bool navWaypointError;  // Werr
};

struct DebugData {
  bool linkTestSuccess;
  unsigned long gpsParseErrors;
  unsigned long gpsSentences;
  unsigned long mainLoopIterations;
  unsigned long sensorUpdates;
  unsigned long navUpdates;
  unsigned long sensorAvgDelayTime;
  unsigned long sensorAvgRunTime;
  unsigned long sensorWorstCaseDelayTime;
  unsigned long sensorWorstCaseRunTime;
  unsigned long navAvgDelayTime;
  unsigned long navAvgRunTime;
  unsigned long navWorstCaseDelayTime;
  unsigned long navWorstCaseRunTime;
  unsigned long averageSerialTime;
  unsigned long spiXmtCount;
  unsigned long spiXmtErrorCount;
};

#endif
