#ifndef APP_H
#define APP_H

#include "config.h"
#include <Vector.h>
#include "types.h"
#include "Addon.h"
#include "common/timer.h"

class DirectionSwitch;
class VFD;
class AutoReverse;
class RMotorControl;
class AutoReverseMode;
class CurrentSensor;
class Status;
class ExtrusionReplay;
class App : public Addon
{

public:
    App();

    DirectionSwitch *dirSwitch;
    VFD *vfd;
    AutoReverse *autoReverse;
    AutoReverseMode *aMode;
    CurrentSensor *cSensor;
    Status *status;
    ExtrusionReplay *exReplay;

    Addon *byId(short id);

    short setup();
    short loop();
    short debug();
    short info();
    short ok();

    void loop_service();
    void loop_shredding();
    void auto_reverse();
    
    void loop_extruding();
    void _loop_motor_manual(bool jamDetection);
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
    millis_t waitTS;
    Timer<10, millis> timer; // 10 concurrent tasks, using micros as resolution
    millis_t lastJam;
    short setOverload(short val);
    short overloaded;

    enum SHRED_STATE
    {
        WAITING = 0,
        INIT = 1,
        POWERED = 2,
        STARTED = 3,
        SHREDDING = 6,
        UNPOWERED = 7,
        DONE = 8,
        CANCELLING = 10,
        JAMMED = 11,
        REVERSING = 12,
        REVERSED = 13,
        STOPPING = 14,
        FORWARDING = 15,
        CANCELLED = 16,
        STUCK = 17
    };
    
    short shredState;
    short shredStateLast;
    short shredCancelState;
    short jamCounter;
    short setShredState(short newState);
    bool isAutoReversing();

    enum APP_STATE
    {
        RESET = 0,
        // SHREDDING = 1,
        ERROR = 5,
        REPLAY = 6,
        RECORD = 7
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