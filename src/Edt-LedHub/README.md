# Edt-LedHub

The LedHub is an ESP32 based system that receives OSC messages over UDP and converts them into animations to be displayed on APA102 based LEDs using FastLED, regular RGB LEDs using a Darlington Array, and possibly other stuff.

It uses Edt-Core and Edt-CoreDevices for the commons stuff, and processes UDP messages on the main Arduino thread, and sends them to the queue of the correct output. Each queue is consumed by a dedicated thread that manages animation state.