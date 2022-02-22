#include "CoreApp.h"
#ifdef ETHERNET
#include "Ethernet.h"
#include "EthernetUDP.h"
#endif
#include "HardwareSerial.h"
#include "Statemachine.h"
#include "Time.h"
#include "FastLED.h"
#include "Arduino.h"
#include "OSCArduino.h"
#include "CommandMessage.h"
#include "MessageConsumer.h"
#include "EdtDmx.h"