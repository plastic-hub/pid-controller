#include <Vector.h>
#include <Streaming.h>
#include <Arduino.h>
#include "app.h"
#include "features.h"
#include <MemoryFree.h>
#include "Version.h"

// #define DEBUG_MEM

static Addon *addonsArray[10];

#ifdef HAS_STATES
short App::appState(short nop)
{
    uchar s = addons.size();
    uchar si = 0;
    String out = "";
    uchar l = numByFlag(STATE);
    for (uchar i = 0; i < s; i++)
    {
        Addon *addon = addons[i];
        if (!!(addon->hasFlag(STATE)))
        {
            si++;
            out += addon->state();
            if (si < l)
            {
                out += ",";
            }
        }
    }
    const char *response = Bridge::CreateResponse(STATE_RESPONSE_CODE, 0, out.c_str());
    Serial.write(response);
}
#endif

short App::ok()
{
    return E_OK;
}

App::App() : Addon("APP", APP, 1 << STATE),
#ifdef HAS_STATUS
             status(new Status(STATUS_ERROR_PIN, STATUS_OK_PIN)),
#endif
             cSensor(new CurrentSensor(CURRENT_SENSOR_PIN))
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
    _state = 0;    
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
}

short App::loop()
{
    timer.tick();
    now = millis();
    loop_addons();
    loop_com();
    loop_pid();
    delay(LOOP_DELAY);
}

void App::loop_com()
{
    if (millis() - comTS > 300)
    {
#if defined(HAS_BRIDGE) && defined(HAS_SERIAL)
        PPSerial::Message *msg = serialBridge->read();
        if (msg)
        {
            switch (msg->verb)
            {

            case Bridge::EC_METHOD:
            {
                char *strings[3];
                char *ptr = NULL;
                byte index = 0;

                ptr = strtok(msg->payload, ":");

                while (ptr != NULL && index < 4)
                {
                    strings[index] = ptr;
                    index++;
                    ptr = strtok(NULL, ":");
                }
                
                int id = atoi(strings[0]);
                char *_method = strings[1];

                SKeyVal *method = VSL::instance()->hasMethod(id, _method);
                if (method)
                {
                    int arg = atoi(strings[2]);
                    Addon *addon = (Addon *)method->instance;
                    AddonFnPtr ptr = method->mPtr;
                    short ret = (addon->*ptr)(arg);

                    if (TEST(msg->flags, Bridge::STATE))
                    {
                        #ifdef HAS_STATES
                            this->appState(0);
                        #endif
                    }
                    else if (TEST(msg->flags, Bridge::RECEIPT))
                    {
                        #ifdef BRIDGE_HAS_RESPONSE
                            const char *response = Bridge::CreateResponse(msg->id, 0, ret);
                            Serial.write(response);
                        #endif
                    }
                    if (TEST(msg->flags, Bridge::DEBUG))
                    {
                       // Serial.println("Called command");
                    }
                }
                else
                {
                    VSL::instance()->debug();
                    if (TEST(msg->flags, Bridge::DEBUG))
                    {
                        /*
                        Serial.print("Incoming message, cant find class & method ");
                        Serial.print(_class);
                        Serial.print(":");
                        Serial.print(_method);
                        Serial.print("\n");
                        */
                    }
                }
                break;
            }
            }
            msg->payload = NULL;
        }
#endif
        comTS = millis();
    }
}
