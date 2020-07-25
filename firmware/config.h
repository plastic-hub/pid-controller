#ifndef CONFIG_H
#define CONFIG_H

#include "enums.h"
#include "common/macros.h"
#include <Controllino.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Core settings
//

#define LOOP_DELAY              500         // Our frame time, exluding delays in some places
#define BOOT_DELAY              1000        // Wait at least this amount in ms after boot before doing anything

// Please consider to set this to false for production - especially with the full feature set since this is requiring extra
// time for the serial communication and will affect the overall framerate/performance
// #define DEBUG true

#define DEBUG_INTERVAL          1000
#define DEBUG_BAUD_RATE         19200       // Serial port speed

#define RELAY_ON 0                          // The relay bank's on value (eg: normally closed) 
#define RELAY_OFF 255                       // The relay bank's off value (eg: normally closed) 


#define DIR_SWITCH_UP_PIN       CONTROLLINO_A1           // The 3 position's up output
#define DIR_SWITCH_DOWN_PIN     CONTROLLINO_A0           // The 3 position's down output
// #define IGNORE_FIRST_DIRECTION              // Uncomment to ignore the 3pos switch (forward/reverse) after booting. This prevents surprises but possibly also accidents.
//#define DIR_SWITCH_DELAY        500      // If defined, add this as blocking delay between direction changes. Needed for some types of relays.

#define ANALOG_READ_INTERVAL                    200

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Machine settings
//

// #define USE_MEGA                               // On Arduino Uno we have only limited ports which are not enough to enable all features.
#define USE_CONTROLLINO
// #define HAS_AUTOREVERSE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    VFD related
//

// #define HAS_MODBUS_BRIDGE

// VFD FWD Pin. This goes into the relay and then into the VFD.
#define FWD_PIN                             CONTROLLINO_D5

// VFD REV Pin. This goes into the relay and then into the VFD.
#define REV_PIN                             CONTROLLINO_D4

// the time needed to boot up the VDF, only used when we control also the power via POWER_0
#define VFD_BOOT_TIME   500

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Motor related
//
// IR sensor ( LM393 ) used together with a rotary encoder disc - uncomment to activate
// #define HAS_MOTOR_IR_SENSOR
#define IR_PIN 2                            // Arduino has fixed pins for using interrupts, don't change this
#define IR_INTERVAL         500             // Recompute values in this interval
#define IR_TIMEOUT          1600            // Max. delta time between the sensor's on/off. This is used to recognize a jamming
// #define IR_SPEED                            // Calculate also the speed - needed for addons: injection & printer extension - uncomment to activate

// Motor temperature sensor - uncomment to activate. If the TEMPERTURE_MAX has been exceeded, it will stop the motor and goes into fatal mode.
// #define MOTOR_HAS_TEMPERTURE
#define MOTOR_TEMPERTURE_SCK_PIN  5
#define MOTOR_TEMPERTURE_CS_PIN   6
#define MOTOR_TEMPERTURE_SO_PIN   7

#define MOTOR_TEMPERTURE_INTERVAL 1000            // Sensor read interval, MAX6675 wants it over 1000
#define MOTOR_TEMPERTURE_MAX      50              // Max. motor temperature, in C

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Extrusion related
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Auto-Reverse
//
// Threshold, if after this time the motor doesn't spin, abort!
// That can happen when the shredder or extrusion heavily jammed. Uncomment to activate this feature.
#define STARTING_MIN_TIME       1800        
// Threshold, time needed to have the motor on target speed but incl. some time to have shredded some material. 
// This may depend also on the VFDs primary acceleration time.
#define STARTING_TIMEOUT        3000        

// Threshold, if after that time the motor doesn't spin, abort ! 
// That can happen when the shredder or extrusion heavily jammed. Uncomment to activate this feature.
#define REVERSE_MIN_TIME        1800        
// Threshold, time needed to have the motor on target speed but also rotated for some time.
#define REVERSING_TIMEOUT       3200

// When shredding, stop all after this time. Uncomment to activate.
// This will be only used when AUTO_REVERSE_MODE is not AR_MODE::EXTRUSION.
// That means of course that shredding will always stop after one hour. 
// I considered this a safety feature and will be of importance when the operator is absent unexpectly.
// @TODO: in case there is a VFD speed sensor, or a hall sensor : augment mean deltas to determine 'activity' which
// will then extend the time. It may make sense to apply this feature also for extruding then.
#define MAX_SHRED_TIME          MIN_MS
#define MAX_IDLE_TIME           SECS * 20

#define MAX_REVERSE_TRIALS      1           // Max. trials to reverse before aborting (goes in FATAL state, unlock via 3pos switch = 0 or reset button)

#define AUTO_REVERSE_DELAY      1000        // When instructing direction changes, put this as delay in between. This is needed with certain relays which may require a delay.

// The pin to disable/enable auto-reverse - uncomment to activate
// This is for a 2 state toggle switch and is intented for using this on a shredder only.
// For extrusion & shredder combos, please use a 3 state switch instead ('HAS_AUTO_REVERSE_MODE')
// #define ENABLE_AUTO_REVERSE_PIN 10       
#define SHOW_REVERSE_STATUS                 // If defined and there are status lights, toggle the OK LED for indicating reversing
// #define HAS_AUTO_REVERSE_MODE               // 3pos switch to switch between: auto-reverse, extruding and none
#define AUTO_REVERSE_MODE_UP_PIN                CONTROLLINO_A3
#define AUTO_REVERSE_MODE_DOWN_PIN              CONTROLLINO_A2

#define ANALOG_LEVEL_POWERED                    275
#define ANALOG_LEVEL_UNPOWERED                  475

// In some cases it makes sense to disable extrusion reverse entirely. Set this to false otherwise.
// This setting will be only used if AUTO_REVERSE_MODE is set to AR_MODE::EXTRUSION. 
// In later versions this will be refined with the MachineFeatures flags.
#define ALLOW_EXTRUSION_REVERSE     true 

#define HAS_AUTO_REVERSE

#define CURRENT_SENSOR_PIN                      CONTROLLINO_IN0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    General switches

// Reset button - uncomment to activate. This will unlock the fatal state in case of jamming or other problems.
//#define HAS_RESET
#define RESET_PIN           3
#define RESET_DELAY         1000            // Time to wait when reset has been hit or hold. This is good to give the system some time
#define RESET_FATAL         true            // Makes the reset button act as emergency button. User has to go into stop positon first to unlock it again otherwise it keeps spinning after the RESET_DELAY
#define RESET_INTERVAL      300             // Interval to read the NC reset button
#define RESET_NC            true            // Toggles the reset button type between NC and NO

// Operation Mode Switch

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Feedback

// Status LEDS (ok, error) - uncomment to activate
#define HAS_STATUS
#define STATUS_OK_PIN                                   CONTROLLINO_D2
#define STATUS_ERROR_PIN                                CONTROLLINO_D3

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Extrusion Replay 

#define HAS_EXTRUSION_REPLAY
#define EXTRUSION_RECORD_PIN                            CONTROLLINO_A5
#define EXTRUSION_REPLAY_PIN                            CONTROLLINO_A4
#define EXTRUSION_REPLAY_LEVEL                          700

#define FIRMWARE_VERSION 0.7

////////////////////////////////////////////////////////////////
//
// HMI Bridge 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    externals
//

// pull in internal constants
#include "constants.h"

// pull in internal configs
#include "config_adv.h"

// The user_config.h is initially added to the github repository but changes will be ignored via .gitignore. Please keep this file safe and possibly
// on a per tenant base stored. You can override parameters in this file by using #undef SOME_PARAMETER and then re-define again if needed, otherwise disable 
// default features by using #undef FEATURE_OR_PARAMETER.
// This presents the possibilty to play with the code whilst staying in the loop with latest updates.
#include "user_config.h"

// At last we check all configs and spit compiler errors
#include "config_validator.h"

#endif
