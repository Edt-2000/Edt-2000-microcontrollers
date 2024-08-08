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

#include "networking/network.hpp"
#include "networking/websocket.hpp"
// #include "networking/udp.hpp"

#include "animator.hpp"
#include "time.hpp"
#include "settings.hpp"

#include "debugging/logger.hpp"

CRGB *leds = new CRGB[640];

void setup()
{
  // these are all the animations the system knows
  Animator.addAnimation(new BlinkAnimation());
  Animator.addAnimation(new StroboAnimation());

  Serial.begin(115200);

  Network.startWifi();

  FastLED.addLeds<WS2812B, 5, GRB>(leds, 640).setCorrection(TypicalLEDStrip);

  fill_solid(leds, 640, CRGB::Black);
  FastLED.show();

  do
  {
    PrintLnInfo("Waiting for network..");
    delay(100);
  } while (!Network.ethernetIsConnected());

  PrintLnInfo("Network started!");

  JsonDeserializer.onAnimation([](std::string animation)
                               { Animator.changeAnimation(animation); });

  // Udp.begin();
  WebSocket.begin();

  PrintLnInfo("App started!");
}

// this buffer saves the start of the loop, which allows the time class
// to jump to, interrupting the animation loop
jmp_buf loop_jump_buffer;

void loop()
{
  setjmp(loop_jump_buffer);

  do
  {
    Animator.loop();

    // run maintenance logic
    if (Time.t1000ms)
    {
      // TODO: send globalSettings + currentAnimation
      WebSocket.cleanUp();
    }
  } while (true);
}
