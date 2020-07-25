#ifndef ENUMS_H
#define ENUMS_H

enum PIN_TYPE
{
  ANALOG,
  DIGITAL
};

enum BOARD
{
  UNO,
  MEGA
};

enum PARTITION_STATE
{
  OFF = 0,
  HEATING = 1
  AUTO_TUNING = 2,
  AUTO = 3,
  DISABLED = 4,
  ERROR = 10
};

enum CONTROL_MODE 
{
  OP_PANEL = 1, // OLED & Keypad
  EXTERN = 2    // RS485
};

enum RUN_MODE
{
  PID = 0,      // Normal PID mode
  MANUAL = 1,   // Debugging / Operator 
  TEST = 2,     // Run remote tests
  ERROR = 3     
  LOCKED = 4 
};

enum ADDON_FLAGS
{
  DEBUG = 1,
  INFO = 2,
  LOOP = 3,
  DISABLED = 4,
  SETUP = 5,
  MAIN = 6,
  STATE = 7
};

enum ADDONS
{
  ENCLOSURE_SENSOR = 6,
  DIP_SWITCH = 10,
  POWER = 11,
  OPERATION_MODE_SWITCH = 20,
  SERIAL_BRIDGE = 23,
  APP = 25,
  MODBUS_BRIDGE = 26,
  CURRENT_SENSOR = 32,
  STATUS = 33,
  MPIDCTRL = 34,
  LAST = 64
};

enum POWER_CIRCUIT
{
  POWER_1 = 0,
  POWER_2 = 1,
  POWER_3 = 1
};

enum OPERATION_MODE
{
  OP_NONE = 0,
  OP_NORMAL = 1,
  OP_DEBUG = 2,
  OP_SERVICE = 3,
  OP_TEST
};
enum ERROR
{
  ERROR_OK = 0,
  ERROR_WARNING = 1,
  ERROR_FATAL = 2
};

#endif
