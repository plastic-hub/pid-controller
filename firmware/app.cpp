#include <Vector.h>
#include <Streaming.h>
#include <Arduino.h>

#include "app.h"
#include "features.h"
#include <MemoryFree.h>

#include "Version.h"

// #define DEBUG_MEM

static Addon *addonsArray[10];

short App::ok()
{
    return E_OK;
}

App::App() : Addon("APP", APP, 1 << STATE),
#ifdef HAS_DIRECTION_SWITCH
             dirSwitch(new DirectionSwitch()),
#endif
#ifdef HAS_AUTO_REVERSE_MODE
             aMode(new AutoReverseMode(AUTO_REVERSE_MODE_UP_PIN, AUTO_REVERSE_MODE_DOWN_PIN)),
#endif
#ifdef HAS_VFD
             vfd(new VFD()),
#endif
#ifdef HAS_STATUS
             status(new Status(STATUS_ERROR_PIN, STATUS_OK_PIN)),
#endif
#ifdef HAS_EXTRUSION_REPLAY
             exReplay(new ExtrusionReplay(EXTRUSION_RECORD_PIN, EXTRUSION_REPLAY_PIN)),
#endif
             cSensor(new CurrentSensor(CURRENT_SENSOR_PIN)),
             shredStateLast(0),
             shredCancelState(0)
{
}

short App::getAppState(short val)
{
    return _state;
}
void (*resetFunction)(void) = 0; // Self reset (to be used with watchdog)

void printMem()
{
    Serial.print("mem: ");
    Serial.print(freeMemory());
    Serial.println('--');
}
short App::setup()
{
    Serial.begin(DEBUG_BAUD_RATE);
    Serial.print("Booting Firmware ...................... \n\n");
    Serial.print(FIRMWARE_VERSION);
    Serial.print(" | ");
    Serial.print(VERSION);
    Serial.print(" | ");
    Serial.print(CID);
    Serial.println(" - \n");
    addons.setStorage(addonsArray);
    setup_addons();
    
#ifdef MEARSURE_PERFORMANCE
    printPerfTS = 0;
    addonLoopTime = 0;
    bridgeLoopTime = 0;
#endif
    debugTS = 0;
    loopTS = 0;
    shredState = 0;
    overloaded = 0;
    _state = 0;
    jamCounter = 0;
    lastJam = 0;
#ifdef DEBUG_MEM
    timer.every(
        5000, [](App *app) -> void {
            printMem();
        },
        this);
#endif
}

void App::onError(int error)
{
    if (_state != ERROR)
    {
#ifdef HAS_STATUS
        status->status_blink(true);
#endif

        _state = ERROR;
    }

    vfd->stop();
}

short App::loop()
{
    timer.tick();
    now = millis();
    loop_addons();
    loopShred();
    delay(LOOP_DELAY);
}
