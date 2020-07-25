#include <Vector.h>
#include <Streaming.h>
#include <Arduino.h>
#include "app.h"
#include "features.h"

// #define HAS_SHRED_DEBUG

#ifdef HAS_SHRED_DEBUG
#define SHRED_DEBUG(A) Serial.println(A);
#else
#define SHRED_DEBUG(A)
#endif

void App::auto_reverse()
{
    switch (shredState)
    {
    case JAMMED:
    {
        SHRED_DEBUG("jammed: reversing");
        shredState = FORWARDING;
        vfd->rev(true);
        jamCounter++;
        lastJam = now;
        timer.in(
            AR_REVERSE_TIME, [](App *app) -> void {
                app->vfd->stop();
                app->shredState = STOPPING;
                SHRED_DEBUG("jammed: stopped");
            },
            this);
        break;
    }
    case STOPPING:
    {
        SHRED_DEBUG("jammed: stopping");
        shredState = FORWARDING;
        timer.in(
            AR_FORWARD_WAIT_TIME, [](App *app) -> void {
                app->shredState = REVERSED;
                SHRED_DEBUG("jammed: stopped");
            },
            this);
        break;
    }
    case FORWARDING:
    {
        delay(1);
        break;
    }
    case REVERSED:
    {
        shredState = FORWARDING;
        if (!cSensor->ok())
        {
            SHRED_DEBUG("jammed: stuck");
            shredState = STUCK;
            break;
        }
        vfd->fwd(true);
        SHRED_DEBUG("jammed: forward");
        timer.in(
            AR_FORWARDING_TIME, [](App *app) -> void {
                if (!app->cSensor->ok())
                {
                    SHRED_DEBUG("jammed: overloaded");
                    if (app->jamCounter > MAX_REVERSE_TRIALS)
                    {
                        SHRED_DEBUG("jammed: stuck");
                        app->shredState = STUCK;
                    }
                    else
                    {
                        SHRED_DEBUG("jammed: still jammed");
                        SHRED_DEBUG(app->jamCounter);
                        app->shredState = JAMMED;
                    }
                }
                else
                {
                    SHRED_DEBUG("jammed: continue with last state");
                    app->shredState = app->shredStateLast;
                    app->lastJam = 0;
                }
            },
            this);
        break;
    }
    }
}

bool App::isAutoReversing()
{
    return shredState == App::SHRED_STATE::JAMMED ||
           shredState == App::SHRED_STATE::REVERSING ||
           shredState == App::SHRED_STATE::REVERSED ||
           shredState == App::SHRED_STATE::STOPPING ||
           shredState == App::SHRED_STATE::FORWARDING;
}

short App::setShredState(short newState)
{
    if (isAutoReversing())
    {
        return App::SHRED_STATE::JAMMED;
    }
    shredState = newState;
    return shredState;
}

void App::loop_shredding()
{
    uchar sw = this->dirSwitch->value();
    if (shredState == STUCK)
    {
        onError(E_MAX_JAM);
        return;
    }

    if (!cSensor->ok())
    {
        if (!isAutoReversing())
        {
            setShredState(JAMMED);
        }
    }

    switch (sw)
    {
    case POS3_DIRECTION::UP:
    {
        if (isAutoReversing())
        {
            auto_reverse();
#ifdef HAS_STATUS
            status->setStatus(true);
#endif
        }
        else
        {
            setShredState(SHREDDING);
            vfd->fwd(true);
        }
        break;
    }
    case POS3_DIRECTION::MIDDLE:
    {
        vfd->stop();
        shredState = DONE;
        break;
    }

    case POS3_DIRECTION::DOWN:
    {
        if (!cSensor->ok())
        {
            onError(ERROR);
            break;
        }

        vfd->rev(true);
        setShredState(SHREDDING);
        break;
    }
    }
#ifdef HAS_STATUS
    status->setStatus(sw);
#endif
}

void App::_loop_motor_manual(bool jamDetection)
{

    if (_state == ERROR)
    {
        return;
    }

#if defined(HAS_DIRECTION_SWITCH) && defined(HAS_VFD)
    uchar sw = this->dirSwitch->value();

    if (jamDetection && sw && !cSensor->ok())
    {
        onError(ERROR);
        return;
    }

    switch (sw)
    {
    case POS3_DIRECTION::UP:
    {
        this->vfd->fwd(true);
        break;
    }
    case POS3_DIRECTION::DOWN:
    {
        this->vfd->rev(true);
        break;
    }
    case POS3_DIRECTION::MIDDLE:
    {
        this->vfd->stop(true);
        break;
    }
    }

#ifdef HAS_STATUS
    status->setStatus(sw);
#endif
#endif
}
ushort App::loopShred()
{
    uchar sw = dirSwitch->value();
    uchar am = aMode->value();

    if (sw && sw == dirSwitch->last())
    {
        onError(ERROR);
        return;
    }

#ifdef HAS_EXTRUSION_REPLAY
    if (!sw && am == AR_MODE::EXTRUSION && _state != ERROR)
    {

        if (exReplay->replay && exReplay->recordTime > 2000)
        {
            _state = REPLAY;
        }

        if (_state == REPLAY)
        {
            if(!cSensor->ok()){
                onError(ERROR);
                return;
            }
            
            if (now - exReplay->lastReplayTS < exReplay->recordTime)
            {
                vfd->fwd(true);
            }else{
                vfd->stop();
                exReplay->replay = false;
                _state = RESET;
            }
            return;
        }

        if (exReplay->recordOn)
        {
            if (cSensor->ok())
            {
                vfd->fwd(true);
            }
            else
            {
                onError(ERROR);
            }
        }
        else
        {
            vfd->stop(true);
        }
        return;
    }
#endif

    // clear error state on pos middle / stop
    if ((_state == ERROR || isAutoReversing()) && sw == POS3_DIRECTION::MIDDLE)
    {
#ifdef HAS_STATUS
        status->status_blink(false);
        status->setStatus(false);
#endif
        _state = RESET;
        shredState = DONE;
        jamCounter = 0;
    }

    switch (am)
    {
    case AR_MODE::EXTRUSION:
    case AR_MODE::NONE:
    {
        _loop_motor_manual(am == AR_MODE::EXTRUSION);
        break;
    }

    case AR_MODE::NORMAL:
    {

        loop_shredding();
        break;
    }
    }
}
