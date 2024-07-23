#pragma once

#include <Arduino.h>
#include <setjmp.h>

extern jmp_buf loop_jump_buffer;

class TimeHelper
{
private:
    volatile unsigned long _previous = micros();
    unsigned int _ms = 0;
    volatile bool _interrupted = false;

public:
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

        if (now - _previous >= 1000UL)
        {
            _previous = now;

            t1ms = true;

            _ms++;

            if (_ms == 1000)
            {
                t10ms = true;
                t100ms = true;
                t1000ms = true;

                // reset ms after 1s
                _ms = 0;
            }
            else if (_ms % 10 == 0)
            {
                t10ms = true;

                if (_ms % 100 == 0)
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
        _interrupted = false;
        unsigned int current = 0;
        do
        {
            vTaskDelay(0);
            loop();

            if (t10ms)
            {
                current += 10;
                if (current >= ms)
                {
                    break;
                }
            }
        } while (!_interrupted);

        if (_interrupted)
        {
            // jump back to the main loop function as the animation loop should be stopped
            longjmp(loop_jump_buffer, 0);
        }
    }
} Time;

extern TimeHelper Time;
