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

auto animationCallback = [](std::string animation)
{
  Animator.changeAnimation(animation);
};
auto stateChangeCallback = []()
{
  PrintLnDebug("WebSocket send message");

  auto json = JsonHandler.serialize(Animator.currentAnimationName());
  WebSocket.send(json);
};

void setup()
{
  // these are all the animations the system knows
  Animator.addAnimation(new BlinkAnimation());
  Animator.addAnimation(new StroboAnimation());

  Serial.begin(115200);

  Network.startEthernet();

  // FastLED.addLeds<WS2812B, 5, GRB>(leds, 640).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 13, 32, BGR, DATA_RATE_KHZ(500)>(leds, 1).setCorrection(TypicalLEDStrip);

  fill_solid(leds, 640, CRGB::Black);
  FastLED.show();

  do
  {
    PrintLnInfo("Waiting for network..");
    delay(100);
  } while (!Network.networkIsConnected());

  PrintLnInfo("Network started!");

  JsonHandler.onAnimation(animationCallback);
  JsonHandler.onStateChange(stateChangeCallback);

  // Udp.begin();
  WebSocket.onStateChange(stateChangeCallback);
  WebSocket.begin();

  PrintLnInfo("App started!");
}

// this buffer saves the start of the loop, which allows the time class
// to jump to, interrupting the animation loop
// --
// by doing a loop inside loop setjump isn't invoked every loop, which
// should help performance
jmp_buf loop_jump_buffer;

void loop()
{
  setjmp(loop_jump_buffer);

  do
  {
    Animator.loop();

    // run maintenance logic + send state to clients
    if (Time.t1000ms)
    {
      WebSocket.cleanUp();

      stateChangeCallback();
    }
  } while (true);
}
