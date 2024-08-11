#pragma once

#include <Arduino.h>
#include <setjmp.h>

extern jmp_buf loop_jump_buffer;

class TimeHelper
{
private:
    volatile unsigned long _next = micros();
    volatile bool _interrupted = false;

public:
    // current milliseconds of the current second
    // resets after 12k
    unsigned int ms = 0;

    bool t1ms;
    bool t10ms;
    bool t100ms;
    bool t1000ms;

    void loop()
    {
        if (t1ms)
        {
            t1ms = false;
            t10ms = false;
            t100ms = false;
            t1000ms = false;
        }

        unsigned long now = micros();
        if (now >= _next)
        {
            _next = now + 1000UL;

            t1ms = true;

            ms++;

            if (ms % 1000 == 0)
            {
                t10ms = true;
                t100ms = true;
                t1000ms = true;

                // reset ms after 10s
                if (ms > 12000) {
                    ms = 0;
                }
            }
            else if (ms % 10 == 0)
            {
                t10ms = true;

                if (ms % 100 == 0)
                {
                    t100ms = true;
                }
            }
        }
    }

    void interrupt()
    {
        _interrupted = true;
    }

    void delay(unsigned int ms)
    {
        unsigned int current = 0;
        do
        {
            vTaskDelay(0);
            loop();

            if (t1ms)
            {
                current += 1;
                if (current >= ms)
                {
                    break;
                }
            }
        } while (!_interrupted);

        if (_interrupted)
        {
            _interrupted = false;
            
            // jump back to the main loop function as the animation loop should be stopped
            longjmp(loop_jump_buffer, 0);
        }
    }

    bool every(unsigned int interval) {
        return t1ms && (ms % interval) == 0;
    }
} Time;

extern TimeHelper Time;
