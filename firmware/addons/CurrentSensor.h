#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include <Arduino.h>
#include <Streaming.h>
#include "../Addon.h"
#include "../config.h"

#include "../common/macros.h"
#include "../common/ppmath.h"

class CurrentSensor : public Addon
{
public:
  CurrentSensor(short _pin) : pin(_pin),
                              load(0),
                              Addon(CURRENT_SENSOR_STR, CURRENT_SENSOR)
  {
    // this->setFlag(DEBUG);
  }

  short setup()
  {
    pinMode(pin, INPUT);
    loop();
  }

  short loop()
  {
    if (now - last > MOTOR_LOAD_READ_INTERVAL)
    {
      load = digitalRead(pin);
      last = now;
    }
    return load;
  }

  short ok()
  {
    return !load;
  }

  void debug(Stream *stream)
  {
    *stream << this->name << ":" << ok();
  }

  void info(Stream *stream)
  {
    *stream << this->name << "\n\t : " SPACE("Pin:" << pin);
  }

  millis_t lastOverload;

protected:
  short pin;
  short load;
};
#endif