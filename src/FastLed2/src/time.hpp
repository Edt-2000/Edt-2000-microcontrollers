#pragma once

#include <Arduino.h>
#include <setjmp.h>

#include "./debugging/logger.hpp"

extern jmp_buf loop_jump_buffer;

class TimeHelper
{
private:
    volatile unsigned long _next = 0;
    volatile unsigned int _diff100ms = 0;
    volatile unsigned int _count100ms = 0;
    volatile bool _interrupted = false;

    void _loop()
    {
        if (t10ms)
        {
            //t1ms = false;
            t10ms = false;
            t100ms = false;
            t1000ms = false;
            t12000ms = false;
        }

        auto now = millis();
        if (now >= _next)
        {
            _diff100ms += 10 + (now - _next);

            _next = now + 10;

            t10ms = true;

            ms+=10;

            //if (ms % 10 == 0)
            //{
                //t10ms = true;

                // PrintDebug(ms);
                // PrintDebug(" ");
                // PrintLnDebug(now);
                // PrintLnDebug("10ms");

                if (_diff100ms > 100)
                {
                    _diff100ms = 0;
                    _count100ms++;

                    t100ms = true;
                    //PrintLnDebug("100ms");

                    if (_count100ms % 10 == 0)
                    {
                        //PrintLnDebug("1s");

                        t1000ms = true;

                        // reset ms after 12s
                        if (_count100ms > 120)
                        {
                            ms = 0;
                            t12000ms = true;
                            _count100ms = 0;
                        }
                    }
                }
            //}
        }
    }

public:
    // current milliseconds of the current second
    // resets after 12k
    unsigned int ms = 0;

    //bool t1ms;
    
    bool t10ms;
    bool t100ms;
    bool t1000ms;
    bool t12000ms;

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
