#ifndef EXTRUSION_REPLAY_H
#define EXTRUSION_REPLAY_H

#include <Arduino.h>
#include <Streaming.h>

#include "../config.h"
#include "../common/macros.h"

class ExtrusionReplay : public Addon
{
public:
  ExtrusionReplay(short _recordPin, short _replayPin) : recordPin(_recordPin),
                                                        replayPin(_replayPin),
                                                        lastRecordTS(0),
                                                        lastReplayTS(0),
                                                        recordTime(0),
                                                        recordOn(false),
                                                        replayOn(false),
                                                        Addon(EXTRUSION_REPLAY_STR, EXTRUSION_REPLAY)
  {
  }



  void info(Stream *stream)
  {
    *stream << this->name << "\n\t : " SPACE("Record pin:" << recordPin) << SPACE("\t | Replay Pin :" << replayPin);
  }

  short setup()
  {
  }
  short ok()
  {
  }

  short loop()
  {
    read();
  }

  short read()
  {
    bool _recordOn = RANGE(analogRead(recordPin), EXTRUSION_REPLAY_LEVEL - 100, 1024);
    if (!recordOn && _recordOn)
    {
      lastRecordTS = now;
      recordOn = true;
      recordTime = 0;
    }

    if (recordOn && !_recordOn)
    {
      recordTime = now - lastRecordTS;
      recordOn = false;
    }

    bool _replayOn = RANGE(analogRead(replayPin), EXTRUSION_REPLAY_LEVEL - 100, 1024);
    if (_replayOn && !replayOn)
    {
      replayOn = _replayOn;
      lastReplayTS = now;
      replay = true;
    }

    if (!_replayOn && replayOn)
    {
      replayOn = false;
    }
  }

  void debug(Stream *stream)
  {
    *stream << this->name << ":" << SPACE(recordTime);
  }
  
  millis_t recordTime;
  bool recordOn;
  millis_t lastReplayTS;
  bool replayOn;
  bool replay;

private:
  short recordPin;
  short replayPin;
  millis_t lastRecordTS;
};
#endif