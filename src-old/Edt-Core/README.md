# Edt-Core

Edt-Core is the core library of all Edt-2000 microcontrollers. It contains the 
startup state machine, communication libraries and common functions.

## Startup state machine

Each Edt-2000 microcontroller starts up with a distinct blinking pattern to
indicate boot success, and possible failures.

1. After the boot, the state machine starts with a solid ON for 2 seconds.
2. During initialization of networking, the controller blinks with 500 ms intervals.
3. During initialization of controller specific-functionality, the controller blinks with
250ms intervals.
4. When all initialization is complete, the controller signals success by blinking in reducing
intervals. Per interval the interval is reduced by half, giving of an effect reminiscent of a ball
bouncing on a surface. After completion of this effect, full control is given to the main loop of
the controller and the controller can start working.