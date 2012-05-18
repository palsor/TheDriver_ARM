#include "Communication.h"

//
// constructor
// 
Communication::Communication() {}

//
// init
//
void Communication::init() {
  structToTrans = 0;
  commData.dmaInProgress = false;
}

//
// sendData - send data over serial via DMA, protocol is [AAAA][struct_id][data][5555][checksum], only data is included in checksum
//
void Communication::setupDataToSend() {
  
  if (!commData.dmaInProgress) {
    // figure out which struct to send and update commData
    switch (structToTrans) {
      case SENSOR_DATA:
        commData.bufferLength = sizeof(SensorData);
        commData.bufferPointer = (uint8*)&sensorData;
        break;
      case NAV_DATA:
        commData.bufferLength = sizeof(NavData);
        commData.bufferPointer = (uint8*)&navData;
        break;
      case PILOT_DATA:
        commData.bufferLength = sizeof(PilotData);
        commData.bufferPointer = (uint8*)&pilotData;
        break;
      case CAPT_DATA:
        commData.bufferLength = sizeof(CaptData);
        commData.bufferPointer = (uint8*)&captData;
        break;
    }
    commData.bufferLength += MSG_WRAPPER_SIZE;  

    // build the buffer to send
    uint8 checksum = 0;
  
    transmitBuffer[0] = 0xAA;
    transmitBuffer[1] = 0xAA;
    transmitBuffer[2] = structToTrans;
    for (int i = 0; i < commData.bufferLength; i++) {
      transmitBuffer[i + 3] = *(commData.bufferPointer + i);
      checksum += *(commData.bufferPointer + i);  
    }
    transmitBuffer[commData.bufferLength + 3] = checksum;
    transmitBuffer[commData.bufferLength + 4] = 0x55;
    transmitBuffer[commData.bufferLength + 5] = 0x55;
  
    // prep for next transmition
    structToTrans++;
  }
}



