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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Machine settings
//

// #define USE_MEGA                               // On Arduino Uno we have only limited ports which are not enough to enable all features.
#define USE_CONTROLLINO
// #define HAS_AUTOREVERSE

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
//    Heating Cell/Partition


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//    Feedback

// Status LEDS (ok, error) - uncomment to activate
#define HAS_STATUS
#define STATUS_OK_PIN                                   CONTROLLINO_D2
#define STATUS_ERROR_PIN                                CONTROLLINO_D3


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
