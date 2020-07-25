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
    MultiPIDController() : Addon(MPID_CTRL_STR, MPIDCTRL, ADDON_STATED)
    {
        this->setFlag(DEBUG);
    }

private:
    Partition *partions[MAX_PARTITIONS];
};

#endif
