#ifndef HOPPERLOADED_H
#define HOPPERLOADED_H
#ifdef HAS_STATES
#include <ArduinoJson.h>
#endif

#include <Streaming.h>
#include "../Addon.h"
#include "../config.h"
#include "../common/macros.h"
#include "../components/PhotoElectricSensor.h"

// Addon to detect when there is something in the hopper
class HopperLoaded : public Addon
{
private:
  PhotoElectricSensor sensor0;
#ifdef HOPPER_LOADED_1
  PhotoElectricSensor sensor1;
#endif

public:
#ifdef HAS_STATES
  String HopperLoaded::state()
  {
    const int capacity = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<capacity> doc;
    doc["0"] = id;
    doc["1"] = ok() ? 1 : 0;
    return doc.as<String>();
  }
#endif

#ifdef HOPPER_LOADED_1
  HopperLoaded(short h1Pin, short h2Pin) : sensor0(h1Pin, HOPPER_LOADED_INTERVAL),
                                           sensor1(h2Pin, HOPPER_LOADED_INTERVAL),
                                           Addon(HOPPER_LOADED_STR, HOPPER_LOADED, ADDON_STATED)
  {
    // this->setFlag(DEBUG);
  }
#else
  HopperLoaded(short h1Pin) : sensor0(h1Pin, HOPPER_LOADED_INTERVAL),
                              Addon(HOPPER_LOADED_STR, HOPPER_LOADED)
  {
    // this->setFlag(DEBUG);
  }
#endif

  virtual short loop()
  {
#ifdef HOPPER_LOADED_1
    this->sensor0.loop();
    this->sensor1.loop();
#else
    this->sensor0.loop();
#endif
  }

#ifdef TESTING
  // test override
  virtual short ok()
  {
    return test;
  }
#else
  virtual short ok()
  {
    return sensor0.ok(); // || sensor1.ok();
  }
#endif

  void debug(Stream *stream)
  {
    // *stream << this->name << ":" << this->ok() << "\n\t" << SPACE("h ts " << this->sensor0.highTS) << "\n\t" << SPACE("l ts " << this->sensor0.lowTS) << "\n\t" << SPACE("dt  " << this->sensor0.dt);
  }
  void info(Stream *stream)
  {
#ifdef HOPPER_LOADED_1
    *stream << this->name << "\n\t : " << SPACE("HOPPER LOADED 0" << HOPPER_LOADED_0) << SPACE("HOPPER LOADED 1" << HOPPER_LOADED_1);
#endif
  }
#ifdef TESTING
  bool test;
#endif
};

#endif