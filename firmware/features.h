#ifndef FEATURES_H
#define FEATURES_H

#ifdef HAS_SOUND
  #include "alarm.h"
#endif

#ifdef HAS_HALL
  #include "hall.h"
#endif

#ifdef HAS_STATUS
  #include "addons/Status.h"
#endif

#ifdef HAS_RESET
  #include "reset.h"
#endif

#ifdef ENABLE_AUTO_REVERSE_PIN
  #include "auto-reverse-button.h"
#endif

#ifdef HAS_AUTO_REVERSE_MODE
  #include "auto-reverse-mode-switch.h"
#endif

#if defined(HOPPER_DOOR_PIN) || defined(HOPPER_PIN)
  #include "hopper.h"
  #define HAS_HOPPER
#endif

#ifdef HOPPER_FEED_SENSOR
  #include "shredder-feed.h"
#endif

#ifdef SUSPEND_PIN
  #include "suspend.h"
#endif

#ifdef RESUME_PIN
  #include "resume.h"
#endif

#ifdef HAS_AUTOREVERSE
  #include "auto-reverse.h"
  #ifdef HAS_IR
    #include "IRSensor.h"
  #endif
#endif

#if defined(AUTO_REVERSE_MODE_UP_PIN) && defined(AUTO_REVERSE_MODE_DOWN_PIN)
  #include "addons/AutoReverseMode.h"
  #define HAS_AUTO_REVERSE_MODE
#endif

#if defined(FWD_PIN) && defined(REV_PIN)
  #include "addons/DirectionSwitch.h"
  #define HAS_DIRECTION_SWITCH
#endif

#ifdef HAS_AUTOREVERSE
  #include "../Auto-Reverse.h"
#endif

#if defined(FWD_PIN) && defined(REV_PIN)
  #include "VFD.h"
  #define HAS_VFD
#endif

#include "addons/CurrentSensor.h"

#ifdef HAS_STATUS
  #include "addons/Status.h"
#endif

#ifdef HAS_EXTRUSION_REPLAY
  #include "addons/ExtrusionReplay.h"
#endif

#endif