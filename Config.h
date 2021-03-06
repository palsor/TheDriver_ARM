#ifndef CONFIG_H
#define CONFIG_H

// program flow
#define WAIT_FOR_GPS_LOCK 1
//#define WAIT_FOR_SLAVE_ACK
#define TEST_LINK_DURATION 5000  // ms
#define TEST_LINK_ERROR_THRESHOLD 0.01  // 1%

// pins
#define AIRSPEED_PIN 6
#define YAW_SERVO_PIN 9
#define PITCH_SERVO_PIN 6
#define ROLL_SERVO_PIN 5
#define THROTTLE_SERVO_PIN 3

// mechanical controls
#define PITCH_CENTER_ANGLE 90  // approximate steering on-center angle for servo
#define PITCH_MECHANICAL_MAX 25  // mechanical limits of servo travel
#define YAW_CENTER_ANGLE 90  // approximate steering on-center angle for servo
#define YAW_MECHANICAL_MAX 25  // mechanical limits of servo travel
#define ROLL_CENTER_ANGLE 90  // approximate steering on-center angle for servo
#define ROLL_MECHANICAL_MAX 25  // mechanical limits of servo travel

// sensor configs
#define GYRO_X_SIGN -1
#define GYRO_Y_SIGN 1
#define GYRO_Z_SIGN -1
#define ACCEL_X_SIGN 1
#define ACCEL_Y_SIGN -1
#define ACCEL_Z_SIGN -1
#define MAG_X_SIGN 1
#define MAG_Y_SIGN -1
#define MAG_Z_SIGN 1

// bus config
#define GPS_SERIAL_PORT 1
#define GPS_SERIAL_RATE 38400
#define RADIO_SERIAL_PORT 3
#define RADIO_SERIAL_RATE 57600
#define SPI_PORT 2
#define I2C_PORT 1
#define I2C_MODE I2C_FAST_MODE

// debug config
#define NAV_DEBUG 0
#define PILOT_DEBUG 0
#define CONTROLLER_DEBUG 0 
#define COMPASS_DEBUG 0
#define GPS_DEBUG 0

// sensor controls
#define CALIBRATION_ROUNDS 5
#define MAG_DECLINATION -6

// analog settings
#define VREF 3.3
#define MAX_ADC_RANGE 4095

// DCM controls
#define GYRO_WEIGHT 0.5
#define MAG_WEIGHT 0.25
#define ACCEL_WEIGHT 0.25

// Navigator controls
#define EARTH_RADIUS 6371  // km avg earth radius
#define MAX_WAYPOINTS 7
#define HOLD_PATTERN_WAYPOINTS 8
#define HOLD_PATTERN_RADIUS 0.050  // km
#define STATE_INIT -4
#define STATE_END -3
#define STATE_GLIDE -2
#define STATE_RECOVER -1
#define STATE_START 0
#define START_DURATION 3000 // ms
#define STATE_TAKEOFF 1
#define TAKEOFF_DURATION 3000  // ms
#define STATE_CLIMB 2
#define STATE_NAVIGATE 3
#define INVALID_NAV -1
#define ARRIVED_THRESHOLD 0.02

// dynamics
#define MIN_AIR_SPEED 5.14  // m/s ~11 mph
#define CRUISE_AIR_SPEED 12.86  // m/s ~28.7 mph
#define MAX_AIR_SPEED 22.35  // m/s ~50 mph

#define CONTROL_BEARING_THRESHOLD 10.0  // degrees
#define MAX_YAW_RATE 30.0  // degrees/sec

#define CRUISE_ALTITUDE 350.0  // m ~800 ft
#define CONTROL_ALTITUDE_THRESHOLD 10.0  // at CRUISE_ALTITUDE+/-CRUISE_ALTITUDE_THRESHOLD pitch control reaches +/- PITCH_MAX 
#define MAX_PITCH_ANGLE 20.0  // degrees
#define MAX_PITCH_RATE 5.0  // degrees/second
#define ADAPTIVE_PITCH_LIMIT 10.0  // degrees limit of adaptive pitch
#define ADAPTIVE_PITCH_MAX_INCREMENT 1.0  // degrees
#define ADAPTIVE_PITCH_TIMEOUT 300000  // ms 5 minutes

#define THROTTLE_MAX_RATE 25.0  // %/sec
#define THROTTLE_MIN 10.0  // %
#define THROTTLE_MAX 90.0  // %

// mechanical controls
#define ELEVATOR_SERVO_POLARITY -1.0  //  1 normal polarity; -1 reverse polarity of elevator servo
#define MAX_ELEVATOR_SERVO_RATE 400.0  // max degrees/second of servo
#define ELEVATOR_CENTER_ANGLE 90  // approximate steering on-center angle for servo
#define ELEVATOR_MECHANICAL_MAX 25  // mechanical limits of servo travel
#define RUDDER_SERVO_POLARITY -1.0  // 1 normal polarity; -1 reverse polarity of yaw servo
#define MAX_RUDDER_SERVO_RATE 400.0  // max degrees/second of servo
#define RUDDER_CENTER_ANGLE 90  // approximate steering on-center angle for servo
#define RUDDER_MECHANICAL_MAX 25  // mechanical limits of servo travel
#define AILERON_CENTER_ANGLE 90  // approximate steering on-center angle for servo
#define AILERON_MECHANICAL_MAX 25  // mechanical limits of servo travel

#endif
