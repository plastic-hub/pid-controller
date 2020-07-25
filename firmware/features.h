#ifndef FEATURES_H
#define FEATURES_H

#ifdef HAS_RESET
  #include "reset.h"
#endif

#include "addons/CurrentSensor.h"

#ifdef HAS_STATUS
  #include "addons/Status.h"
#endif

#endif