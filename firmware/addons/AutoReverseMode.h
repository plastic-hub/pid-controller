
#ifndef AUTO_REVERSE_MODE_H
#define AUTO_REVERSE_MODE_H

#include "../config.h"
#include "../components/3PosAnalog.h"
#include "../Addon.h"
#include <Streaming.h>
#include "../common/macros.h"

class AutoReverseMode : public Addon
{
public:
  Pos3Analog dir_switch;
  AutoReverseMode(short up, short down) : dir_switch(up, down),
                                          Addon(AUTO_REVERSE_MODE_STR, AUTO_REVERSE_MODE)
  {
    // setFlag(DEBUG);
  }

  void debug(Stream *stream)
  {
    *stream << this->name << ":" << SPACE(dir_switch.switch_pos) << SPACE(dir_switch.last_switch) << SPACE(_value) " | ";
  }
  void info(Stream *stream)
  {
    *stream << this->name << "\n\t : " SPACE("Up Pin:" << dir_switch.upPin) << SPACE("\t | Down Pin :" << dir_switch.downPin);
  }
  short setup()
  {
    dir_switch.setup();
    dir_switch.loop();
    return loop();
  }
  short loop()
  {
    if (now - dt > ANALOG_READ_INTERVAL)
    {

      _value = dir_switch.loop();
      switch (_value)
      {
      case POS3_DIRECTION::UP:
      {
        _value = AR_MODE::NORMAL;
        break;
      }
      case POS3_DIRECTION::MIDDLE:
      {
        _value = AR_MODE::NONE;
        break;
      }
      case POS3_DIRECTION::DOWN:
      {
        _value = AR_MODE::EXTRUSION;
        break;
      }
      }
      dt = now;
    }
    return _value;
  }

  short value()
  {
    return _value;
  }

private:
  short _value;
};

#endif
