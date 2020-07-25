#ifndef MULTI_PID_CONTROLLER_H
#define MULTI_PID_CONTROLLER_H

#include <Arduino.h>
#include <Streaming.h>
#include "../Addon.h"
#include "../config.h"

#include "./common/macros.h"
#include "./common/ppmath.h"

class Partition;

class MultiPIDController : public Addon
{
public:
    MultiPIDController() : Addon(CURRENT_SENSOR_STR, MPIDCTRL)
    {
        this->setFlag(DEBUG);
    }

private:
    Partition *partions[MAX_PARTITIONS];
};

#endif
