#ifndef POS3_ANALOG_H
#define POS3_ANALOG_H

#include <Arduino.h>
#include "../enums.h"
#include "../common/ppmath.h"

class Pos3Analog
{
public:
   Pos3Analog(short _upPin, short _downPin) : upPin(_upPin), downPin(_downPin)
   {
   }

   short setup()
   {
      pinMode(upPin, INPUT_PULLUP);
      pinMode(downPin, INPUT_PULLUP);
      last_switch = loop();
      return 0;
   }

   short loop()
   {
      uchar newDirection = this->read();

      if (newDirection != this->switch_pos)
      {
         this->last_switch = this->switch_pos;
      }
      this->switch_pos = newDirection;
      return this->switch_pos;
   }

   short last_switch = -1; // Track last switch position
   short switch_pos = -1;  // Current switch position
   short upPin;
   short downPin;
   

private:
   uchar read()
   {

      bool up = RANGE(analogRead(upPin), 240, 260);
      bool down = RANGE(analogRead(downPin), 240, 260);

      uchar newDirection = 0;

      if (up)
      {
         newDirection = POS3_DIRECTION::UP;
      }
      if (down)
      {
         newDirection = POS3_DIRECTION::DOWN;
      }
      if (!up && !down)
      {
         newDirection = POS3_DIRECTION::MIDDLE;
      }
      if (up && down)
      {
         newDirection = POS3_DIRECTION::INVALID;
      }
      return newDirection;
   }

   bool changed()
   {
      return last_switch != switch_pos;
   }

   bool clear()
   {
      return last_switch = switch_pos;
   }
};

#endif
