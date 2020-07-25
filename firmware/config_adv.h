#ifndef CONFIG_ADV_H
#define CONFIG_ADV_H

////////////////////////////////////////////////////////////////////////////////
//  
//  Auto reverse time settings

// the time used to reverse after jamming
#define AR_REVERSE_TIME                                 3500

// after reversing came to stop, this is the delay 
// before it's forwarding
#define AR_FORWARD_WAIT_TIME                            100

// after the delay AR_FORWARD_WAIT_TIME, we set the VFD to forward
// by this time, motor / VFD specifc
#define AR_FORWARDING_TIME                              3500

/////////////////////////////////////////////////////////////
//
// Motor load settings, this requires a current sensor or can be
// taken from the VFD's output. 

// the interval to read the current
#define MOTOR_LOAD_READ_INTERVAL                        100

// the current measured when the motor runs idle, min - max range
#define MOTOR_IDLE_LOAD_RANGE_MIN                       30
#define MOTOR_IDLE_LOAD_RANGE_MAX                       50

// the current measured when the motor is under load, min - max range
#define MOTOR_SHREDDING_LOAD_RANGE_MIN                  50
#define MOTOR_SHREDDING_LOAD_RANGE_MAX                  99

// the current measured when the motor is overloaded, min - max range
#define MOTOR_OVERLOAD_RANGE_MIN                        100
#define MOTOR_OVERLOAD_RANGE_MAX                        400

#define MOTOR_MIN_DT                                    2500

//  Error codes
//
#define E_MSG_OK            "Ok"
#define E_MSG_STUCK         "Shredder is stuck"

// common operating failures
#define E_OK                0                           //all good
#define E_STUCK             100                         //Shredder stuck

// power failures

// sensor failures

////////////////////////////
//
// sub system failures
//

// auto-reverse
#define E_MAX_JAM           400                 // we're stuck for real

#endif