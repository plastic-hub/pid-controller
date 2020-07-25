#ifndef APP_H
#define APP_H

#include "config.h"
#include <Vector.h>
#include "types.h"
#include "Addon.h"
#include "common/timer.h"

class DirectionSwitch;
class CurrentSensor;
class Status;
class PPSerial;
class ModbusBridge;

class App : public Addon
{

public:
    App();

    DirectionSwitch *dirSwitch;
    CurrentSensor *cSensor;
    Status *status;

    PPSerial *serialBridge;
    ModbusBridge *modbusBridge;

    Addon *byId(short id);

    short setup();
    short loop();
    short debug();
    short info();
    short ok();

    void loop_service();
    void loop_com();
    void loop_simulate();
    void loop_pid();
    void loop_addons();
    void setup_addons();    
    void onDidSetupAddons();

    ushort numByFlag(ushort flag);
    short shred(short value = 0);
    ushort loopShred();
    void loopShredCancel();

    void onError(int error);

    Vector<Addon *> addons;

    // bridge
    short setFlag(ushort addonId, ushort flag);

#ifdef HAS_STATES
    short appState(short nop = 0);
    String state();
#endif

    millis_t loopTS;
    millis_t wait;
    millis_t comTS;
    millis_t waitTS;
    Timer<10, millis> timer; // 10 concurrent tasks, using micros as resolution
    
    enum APP_STATE
    {
        RESET = 0,
        ERROR = 5        
    };

    short _state;
    short _error;
    short getLastError(short val = 0){
        return _error;
    }
    short setLastError(short val = 0);
    short setAppState(short newState);
    short getAppState(short val);

private:

#ifdef MEARSURE_PERFORMANCE
    millis_t addonLoopTime;
    millis_t bridgeLoopTime;
    millis_t printPerfTS;
#endif

    millis_t debugTS;
};

#endif