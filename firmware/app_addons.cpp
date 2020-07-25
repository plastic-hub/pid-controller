#include <Vector.h>
#include <Streaming.h>
#include <Arduino.h>
#include "app.h"
#include "config.h"
#include "types.h"
#include "common/macros.h"
#include "Addon.h"
#include "features.h"


void App::onDidSetupAddons(){
    
    #ifdef HAS_STATUS
        status->setStatusAllOn();
        delay(SECS * 2);
        status->setStatusAllOff();
        status->setStatus(false);
    #endif
}

short App::setFlag(ushort addonId, ushort flag)
{
    Addon *addon = byId(addonId);
    if (addon)
    {
        addon->setFlag(flag);
        return E_OK;
    }
    return ERROR_WARNING;
}

ushort App::numByFlag(ushort flag)
{
    uchar s = addons.size();
    uchar l = 0;
    String out = "";
    for (uchar i = 0; i < s; i++)
    {
        Addon *addon = addons[i];
        if (!!(addon->hasFlag(flag)))
        {
            l++;
        }
    }
    return l;
}

short App::debug()
{
#ifndef MEARSURE_PERFORMANCE
    if (millis() - debugTS > DEBUG_INTERVAL)
    {
        uchar s = addons.size();
        uchar nb = 0;
        for (uchar i = 0; i < s; i++)
        {
            Addon *addon = addons[i];
            if (addon->hasFlag(DEBUG))
            {
                (addon->debug)(&Serial);
                Serial.println("\n");
                nb++;
            }
        }
        if (nb)
        {
            Serial.println("\n");
        }
        debugTS = millis();
    }
#endif
}

short App::info()
{
    Serial.print("Addon configuration :  \n\n");
    uchar s = addons.size();
    for (uchar i = 0; i < s; i++)
    {
        Addon *addon = addons[i];
        if (addon->hasFlag(INFO))
        {
            addon->info(&Serial);
            Serial << "\n";
        }
    }
}

Addon *App::byId(short id)
{
    uchar s = addons.size();
    for (uchar i = 0; i < s; i++)
    {
        Addon *addon = addons[i];
        if (addon->id == id)
        {
            return addon;
        }
    }
    return NULL;
}

void App::setup_addons()
{
#ifdef HAS_DIRECTION_SWITCH
    addons.push_back((Addon *)dirSwitch);
#endif

#ifdef HAS_VFD
    addons.push_back((Addon *)vfd);
#endif

#ifdef HAS_AUTO_REVERSE_MODE
    addons.push_back((Addon *)aMode);
#endif

#ifdef HAS_STATUS
    addons.push_back((Addon *)status);
#endif
#ifdef HAS_EXTRUSION_REPLAY
    addons.push_back((Addon *)exReplay);
#endif

    addons.push_back((Addon *)cSensor);
    addons.push_back((Addon *)this);

    uchar s = addons.size();
    for (uchar i = 0; i < s; i++)
    {
        Addon *addon = addons[i];
        if (addon->hasFlag(SETUP))
        {
            addon->setup();
        }
    }

    onDidSetupAddons();
}
void App::loop_addons()
{

#ifdef MEARSURE_PERFORMANCE
    millis_t now = millis();
#endif

    uchar s = addons.size();
    for (uchar i = 0; i < s; i++)
    {
        Addon *addon = addons[i];
        if (addon->hasFlag(LOOP))
        {
            addon->now = now;
            addon->loop();
        }
    }

#ifdef MEARSURE_PERFORMANCE
    addonLoopTime = millis() - now;
    if (millis() - printPerfTS > 3000)
    {
        printPerfTS = now;
        Serial << SPACE("Addon loop time") << addonLoopTime << "\n";
    }
#endif
    debug();
}
