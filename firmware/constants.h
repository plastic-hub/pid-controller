#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "enums.h"

/////////////////////////////////////////////////////////////////////////
//
//  Primary - Motor related (shredder, extrusion, grinder)

#define MOTOR_FREQ_NORMAL 50 // set this to 60 Hz if needed
#define MOTOR_RPM 1480       // the actual motor speed
#define MOTOR_REDUCTION 0.03 // ie: 0.03 means 1:30

// Thresholds

// the maximum override in %, eg: 0.5 = 50% and it's not recommeded to run
// the motor below 50% of it's designed operating frequency - it's getting hot
#define MOTOR_LOW_FREQ_LIMIT 0.50
// the maximum override in %, eg: 0.5 = 50% and it's not recommeded to run
// the motor above 50% of it's designed operating frequency
#define MOTOR_HIGH_FREQ_LIMIT 0.50

// - PRE-CALCS
#define MOTOR_FREQ_CMIN MOTOR_FREQ_NORMAL - (MOTOR_FREQ_NORMAL * MOTOR_LOW_FREQ_LIMIT)
#define MOTOR_FREQ_CMAX MOTOR_FREQ_NORMAL + (MOTOR_FREQ_NORMAL * MOTOR_HIGH_FREQ_LIMIT)

/////////////////////////////////////////////////////////////////////////
//
//  Shredder related

// default shredding speed, when chaning machine mode, it will snap to this
// value - if quick speed dial is available or other reasons (eg: remote)
// those values are currently based on v3 observations
#define RPM_SHREDDERING_DEFAULT 60

// min. shredding speed - when in shredder only mode, it won't go below
#define RPM_SHREDDERING_MIN 30

// max. shredding speed - when in shredder only mode, it won't go above
#define RPM_SHREDDERING_MAX 130

/////////////////////////////////////////////////////////////////////////
//
//  Grinder related - Standalone/Combo

// default grinding speed, when chaning machine mode, it will snap to this
// value - if quick speed dial is available or other reasons (eg: remote)
// those values are currently for a 28 mm hexbar
#define RPM_GRINDING_DEFAULT 440

// min. grinding speed - when in grinder only mode, it won't go below
#define RPM_GRINDING_MIN 400

// max. grinding speed - when in grinder only mode, it won't go above
#define RPM_GRINDING_MAX 500

// user - land scaler (ie: radius)
#define RPM_GRINDER_SCALE 1

// transmission ratio from motor to grinder
// ie: 0.03 means 1:30
#define RPM_GRINDER_SHREDDER_SCALE 1

/////////////////////////////////////////////////////////////////////////
//
//  Extrusion related - Standalone

// default extrusion speed, when chaning machine mode, it will snap to this
// value - if quick speed dial is available or other reasons (eg: remote)
#define RPM_EXTRUSION_DEFAULT 50

// min. extrusion speed - when in extrusion only mode, it won't go below
#define RPM_EXTRUSION_MIN 25

// max. extrusion speed - when in extrusion only mode, it won't go above
#define RPM_EXTRUSION_MAX 150

// user - land scaler
#define RPM_EXTRUSION_SCALE 1

/////////////////////////////////////////////////////////////////////////
//
//  VFD - Standalone

// Speed in (VSI)
#define VFD_VSI_MIN_V_SPEED 0 //
#define VFD_VSI_MAX_V_SPEED 5 // most VFDs take speed regulation from 0 - 10
#define VFD_VSI_SCALE 1.0     // For noise, ie: voltage loss

#define VFD_QSPEED_1 1 // VFD quick speed dial profile 1
#define VFD_QSPEED_2 2 // VFD quick speed dial profile 2
#define VFD_QSPEED_3 3 // VFD quick speed dial profile 3
#define VFD_QSPEED_4 4 // VFD quick speed dial profile 4
#define VFD_QSPEED_5 5 // VFD quick speed dial profile 5
#define VFD_QSPEED_6 6 // VFD quick speed dial profile 5

#define ADDON_MOTOR_IDLE "MotorIdle"

/////////////////////////////////////////////////////////////////////////
//
//  Plastic type related scaling
// @TODO : RPM scaling per plastic type

#define RPM_GRINDING_PET 440

/////////////////////////////////////////////////////////////////////////
//
//  Addons
//

#define HOPPER_LOADED_STR "HopperLoaded"
#define MOTOR_IDLE_STR "MotorIdle"
#define EXTRUSION_REPLAY_STR "Extrusion Replay"
#define VFD_STR "VFD"
#define DIRECTION_SWITCH_STR "DirectionSwitch"
#define MOTOR_LOAD_STR "MotorLoad"
#define CURRENT_SENSOR_STR "CurrentSensor"
#define ENCLOSURE_SENSOR_STR "EnclosureSensor"
#define MOTOR_TEMPERATURE_STR "MotorTemperature"
#define POWER_STR "Power"
#define PLUNGER_STR "Plunger"
#define CARTRDIGE_FULL_STR "CartridgeFull"
#define MOTOR_IR_SPEED_STR "MotorIRSpeed"
#define AUTO_REVERSE_STR "AutoReverse"
#define AUTO_REVERSE_MODE_STR "AutoReverseMode"
#define OPERATION_MODE_SWITCH_STR "OperationModeSwitch"
#define APP_STR "App"
#define STATUS_STR "Status LED"
#define RMOTOR_CONTROL_STR "RMotorControl"

#endif