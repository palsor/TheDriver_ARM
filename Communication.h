#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "Config.h"
#include "Externs.h"

#define SENSOR_DATA 0
#define NAV_DATA 1
#define PILOT_DATA 2
#define CAPT_DATA 3

#define MSG_WRAPPER_SIZE 6

class Communication {
  public:
    Communication();
    void init();
    void setupDataToSend();
    
  private:
    int structToTrans;
    uint8 transmitBuffer[200];
};

#endif
