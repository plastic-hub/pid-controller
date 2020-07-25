#ifndef STATUS_H
#define STATUS_H

#include "../addon.h"
#include "../types.h"
#include "../common/macros.h"

#include <Arduino.h>

class Status : public Addon
{
public:
  Status(short _errorPin, short _okPin) : errorPin(_errorPin),
                                          okPin(_okPin),
                                          status_blink_TS(0),
                                          doBlink(false),
                                          last_blink(true),
                                          blink_start_ts(0),
                                          max_blink_time(HOUR_MS),
                                          Addon(STATUS_STR, STATUS)
  {
  }

  short setup()
  {
    pinMode(okPin, OUTPUT);
    pinMode(errorPin, OUTPUT);
  }

  short loop()
  {
    if (now - status_blink_TS > 1000)
    {
      status_blink_TS = millis();
      last_blink = !last_blink;
      if (doBlink)
      {
        digitalWrite(errorPin, last_blink);
      }

      if (now - blink_start_ts > max_blink_time)
      {
        doBlink = false;
      }
    }
  }
  void status_blink(bool blink)
  {
    if (!doBlink && blink)
    {
      blink_start_ts = millis();
    }
    doBlink = blink;
  }

  void setStatusAllOn()
  {
    if (doBlink)
    {
      return;
    }
    digitalWrite(errorPin, HIGH);
    digitalWrite(okPin, HIGH);
  }

  void setStatusAllOff()
  {
    if (doBlink)
    {
      return;
    }
    digitalWrite(errorPin, LOW);
    digitalWrite(okPin, LOW);
  }

  void setStatus(bool error)
  {
    if (doBlink)
    {
      return;
    }
    if (error)
    {
      digitalWrite(errorPin, HIGH);
      digitalWrite(okPin, LOW);
    }
    else
    {
      digitalWrite(okPin, HIGH);
      digitalWrite(errorPin, LOW);
    }
  }

  void info(Stream *stream)
  {
    *stream << this->name << "\n\t : " SPACE("Error Pin:" << errorPin) << SPACE("\t | Ok Pin :" << okPin);
  }

private:
  millis_t status_blink_TS;
  bool doBlink;
  bool last_blink;
  millis_t blink_start_ts;
  millis_t max_blink_time;

  short okPin;
  short errorPin;
};

#endif
