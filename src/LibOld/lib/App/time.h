#pragma once

#include <Arduino.h>

namespace App
{
    class Time
    {
    private:
        unsigned long _now;
        unsigned long _previous;
        int _diff100ms;
        int _t1000ms;

    public:
        // tweakable ticks for when to do certain stuff
        bool tOSC;
        bool tVISUAL;

        // absolute ticks for when to do time sensitive stuff
        bool t100ms;
        bool t1000ms;

        inline void begin()
        {
            tOSC = false;
            t100ms = false;
            t1000ms = false;

            _previous = 0;
            _diff100ms = 0;
            _t1000ms = 0;
        };

        inline void loop()
        {
            _now = ::millis();

            t1000ms = false;
            t100ms = false;

            tVISUAL = (_now - _previous >= 12UL);
            tOSC = (_now - _previous >= 12UL);

            if (tOSC)
            {
                _diff100ms += _now - _previous;

                // use 97 ms to counter bit of delay
                if (_diff100ms >= 197)
                {
                    _diff100ms = 0;
                    t100ms = true;

                    if (++_t1000ms >= 5)
                    {
                        _t1000ms = 0;
                        t1000ms = true;
                    }
                }

                _previous = _now;
            }
        };

        inline unsigned long now()
        {
            return _now;
        }
    };
} // namespace App