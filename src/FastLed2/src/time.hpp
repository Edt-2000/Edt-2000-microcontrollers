#pragma once

#include <Arduino.h>
#include <setjmp.h>

#include "./debugging/logger.hpp"

extern jmp_buf loop_jump_buffer;

class TimeHelper
{
private:
    volatile unsigned long _next10ms;
    volatile unsigned long _next100ms;
    volatile unsigned long _next1000ms;
    // volatile unsigned int _diff100ms;
    // volatile unsigned int _diff1000ms;
    volatile unsigned int _count1000ms;
    volatile bool _interrupted = false;

    void _loop()
    {
        if (t10ms || t100ms || t1000ms)
        {
            // t1ms = false;
            t10ms = false;
            t100ms = false;
            t1000ms = false;
            t12000ms = false;
        }

        auto now = millis();
        if (now >= _next10ms)
        {
            auto diff = now - _next10ms;

            _next10ms = _next10ms + 10;
            ms += 10 + diff;

            t10ms = true;

            // if (ms % 10 == 0)
            //{
            // t10ms = true;

            // PrintDebug(ms);
            // PrintDebug(" ");
            // PrintLnDebug(now);
            // PrintLnDebug("10ms");
        }
        if (now > _next100ms)
        {
            _next100ms = _next100ms + 100;

            // _diff1000ms += _diff100ms;
            //_diff100ms = 0;

            t100ms = true;
            // PrintLnDebug("100ms");
        }
        if (now > _next1000ms)
        {
            _next1000ms = _next1000ms + 1000;

            //_diff1000ms -= 1000;
            _count1000ms++;
            // PrintLnDebug("1s");

            t1000ms = true;

            // reset ms after 12s
            if (_count1000ms > 12)
            {
                ms = 0;
                t12000ms = true;
                _count1000ms = 0;
            }
        }
        //}
    }

public:
    // current milliseconds of the current second
    // resets after 12k
    unsigned int ms = 0;

    // bool t1ms;

    bool t10ms;
    bool t100ms;
    bool t1000ms;
    bool t12000ms;

    inline void setup()
    {
        _next10ms = millis() - 1000;
        _next1000ms = _next100ms = _next10ms;
        // _diff100ms = 0;
        // _diff1000ms = 0;
        _count1000ms = 0;
        _interrupted = false;
    }

    inline void loop()
    {
        // if the main loop calls Time.loop(), there is no need for interruption anymore as we're back where we should have been
        _interrupted = false;
        _loop();
    }

    inline void interrupt()
    {
        _interrupted = true;
    }

    // delay the execution for the given milliseconds
    // will interrupt and end execution automatically
    inline void delay(unsigned int ms)
    {
        unsigned int current = 0;
        do
        {
            vTaskDelay(0);
            _loop();

            if (t10ms)
            {
                current += 10;
                if (current >= ms)
                {
                    break;
                }
            }
        } while (!_interrupted);

        yield();
    }

    // returns true once every interval
    inline bool every(unsigned int interval)
    {
        // TODO: this interval skips a lot and makes things hard
        return interval == 0 || (t10ms && (ms % interval == 0));
    }

    // will interrupt and end execution automatically
    inline void yield()
    {
        if (_interrupted)
        {
            // jump back to the main loop function as the animation loop should be stopped
            longjmp(loop_jump_buffer, 0);
        }
    }
} Time;

extern TimeHelper Time;
