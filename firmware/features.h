#ifndef FEATURES_H
#define FEATURES_H

#ifdef HAS_SOUND
  #include "alarm.h"
#endif


#ifdef HAS_STATUS
  #include "addons/Status.h"
#endif

#ifdef HAS_RESET
  #include "reset.h"
#endif

#ifdef SUSPEND_PIN
  #include "suspend.h"
#endif

#ifdef RESUME_PIN
  #include "resume.h"
#endif

#include "addons/CurrentSensor.h"

#ifdef HAS_STATUS
  #include "addons/Status.h"
#endif

#endif