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

enum POS3_DIRECTION
{
  UP = 1,
  MIDDLE = 0,
  DOWN = 2,
  INVALID = -1
};

enum MODE
{
  /*
  HALT = 0,
  STARTING = 1,
  SHREDDING = 2,
  BREAKING = 3,
  // REVERSING = 4,
  // JAMMING = 5,
  FATAL = 6,
  RESET = 7,
  SUSPENDING = 8,
  SUSPEND = 9,
  RESUMING = 10
  */
};

enum AR_MODE
{
  NORMAL = 1,    // Shredding
  EXTRUSION = 2, // Extrusion (no reverse)
  NONE = 3,      // Disable any jamming detection
  REMOTE = 4     // User land, ie: Firmata, I2C or PlasticHub-Studio
};

enum MACHINE_FEATURES
{
  SHREDDER = 1 << 1,
  EXTRUDER = 1 << 2,
  INJECTOR = 1 << 3,
  GRINDER = 1 << 4,
  PRINTER = 1 << 5
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
  MOTOR_IDLE = 1,
  MOTOR_LOAD = 2,
  MOTOR_TEMPERATURE = 3,
  VFD_CONTROL = 4,
  DIRECTION_SWITCH = 5,
  ENCLOSURE_SENSOR = 6,
  MOTOR_SPEED = 7,
  AUTO_REVERSE = 8,
  CARTRIDGE_FULL_SENSOR_1 = 9,
  DIP_SWITCH = 10,
  POWER = 11,
  OPERATION_MODE_SWITCH = 20,
  HOPPER_LOADED = 21,
  SERIAL_BRIDGE = 23,
  PLUNGER = 24,
  APP = 25,
  MODBUS_BRIDGE = 26,
  RMOTOR_CONTROL = 30,
  AUTO_REVERSE_MODE = 31,
  CURRENT_SENSOR = 32,
  STATUS = 33,
  EXTRUSION_REPLAY = 34,
  LAST = 64
};

enum POWER_CIRCUIT
{
  POWER_PRIMARY = 0,
  POWER_SECONDARY = 1
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
