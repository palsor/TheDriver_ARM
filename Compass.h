#ifndef COMPASS_H
#define COMPASS_H

#include "libmaple_types.h"

#include "Config.h"
#include "Externs.h"

// Mag addresses
#define COMPASS_ADDRESS 0x1E
#define MODE_REGISTER 0x02
#define DATA_REGISTER 0x03

// Mag register values
#define CONTINUOUS_MODE 0

class Compass {
  public:
    Compass();
    void init();
    bool readRawValues(float* mag);
};

#endif
