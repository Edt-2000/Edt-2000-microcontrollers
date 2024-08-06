#include <Arduino.h>
#include <FastLED.h>
#include <AsyncWebSocket.h>
#include <Wifi.h>
#include <ETH.h>
#include <stdio.h>
#include <setjmp.h>

#include "animation.hpp"
#include "animations/blinkAnimation.hpp"
#include "animations/stroboAnimation.hpp"

#include "networking/ethernet.hpp"
#include "networking/websocket.hpp"
// #include "networking/udp.hpp"

#include "animator.hpp"
#include "time.hpp"
#include "settings.hpp"

#include "debugging/logger.hpp"

// my demo board has led "strips" with 1 led
CRGB *leds = new CRGB[1];

void setup()
{
  // these are all the animations the system knows
  Animator.addAnimation(new BlinkAnimation());
  Animator.addAnimation(new StroboAnimation());

  Serial.begin(115200);

  Network.startEthernet(IPAddress(10, 0, 0, 25));

  FastLED.addLeds<APA102, 13, 32, BGR, DATA_RATE_KHZ(500)>(leds, 1).setCorrection(TypicalLEDStrip);
  // my demo board has 2 separate strips - can be removed later
  FastLED.addLeds<APA102, 14, 32, BGR, DATA_RATE_KHZ(500)>(leds, 1).setCorrection(TypicalLEDStrip);

  fill_solid(leds, 1, CRGB::Black);
  FastLED.show();

  do
  {
    PrintLnInfo("Waiting for network..");
    delay(100);
  } while (!Network.ethernetIsConnected());

  PrintLnInfo("Network started!");

  JsonDeserializer.onAnimation([](std::string animation) { Animator.changeAnimation(animation); });

  //Udp.begin();
  WebSocket.begin();

  PrintLnInfo("App started!");
}

// this buffer saves the start of the loop, which allows the time class
// to jump to, interrupting the animation loop
jmp_buf loop_jump_buffer;

void loop()
{
  setjmp(loop_jump_buffer);

  Animator.loop();
  
  // run maintenance logic
  if (Time.t1000ms) {
    WebSocket.cleanUp();
  }
}
