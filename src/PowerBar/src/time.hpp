#pragma once

#include <Arduino.h>
#include <setjmp.h>

#include "./debugging/logger.hpp"

extern jmp_buf loop_jump_buffer;

class TimeHelper
{
private:
    unsigned long _next1ms;
    unsigned long _next20ms;
    unsigned long _next100ms;
    unsigned long _next1000ms;
    uint8_t _count1000ms;
    bool _interrupted = false;

    void _loop()
    {
        if (t1ms)
        {
            t1ms = false;
        }
        if (t20ms || t100ms || t1000ms)
        {
            t20ms = false;
            t100ms = false;
            t1000ms = false;
            t12000ms = false;
        }

        auto now = millis();
        if (now >= _next1ms)
        {
            _next1ms = now + 1;

            t1ms = true;
            ms += 1;

            if (now >= _next20ms)
            {
                auto diff = now - _next20ms;

                _next20ms = now + 20 - diff;

                t20ms = true;

                if (now > _next100ms)
                {
                    diff = now - _next100ms;
                    _next100ms = now + 100 - diff;

                    t100ms = true;

                    if (now > _next1000ms)
                    {
                        diff = now - _next100ms;
                        _next1000ms = now + 1000 - diff;

                        _count1000ms++;

                        t1000ms = true;

                        // reset ms after 12s
                        if (_count1000ms > 12)
                        {
                            ms = 0;
                            t12000ms = true;
                            _count1000ms = 0;
                        }
                    }
                }
            }
        }
    }

public:
    // current milliseconds of the current second
    // resets after 12k
    unsigned int ms = 0;

    bool t1ms;
    bool t20ms;
    bool t100ms;
    bool t1000ms;
    bool t12000ms;

    inline void setup()
    {
        _next1000ms = _next100ms = _next20ms = _next1ms = 0;
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
    inline void delay(unsigned int target)
    {
        unsigned int current = 0;
        do
        {
            vTaskDelay(0);
            _loop();

            if (t1ms)
            {
                current++;
                if (current >= target)
                {
                    break;
                }
            }
        } while (!_interrupted);

        yield();
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

    bool every(unsigned int interval) {
        return t1ms && (ms % interval) == 0;
    }
} Time;

extern TimeHelper Time;
