#include <Arduino.h>
#include <FastLED.h>
#include <AsyncWebSocket.h>
#include <Wifi.h>
#include <ETH.h>
#include <stdio.h>
#include <setjmp.h>

#define NUM_LEDS 640
#define MAX_WIDTH 80

#include "leds.hpp"
#include "font.hpp"

#include "animation.hpp"
#include "animations/fadeTextAnimation.hpp"
#include "animations/glitchTextAnimation.hpp"
#include "animations/noiseAnimation.hpp"
#include "animations/scrollTextAnimation.hpp"
#include "animations/singlePulseAnimation.hpp"
#include "animations/staticTextAnimation.hpp"
#include "animations/stroboAnimation.hpp"
#include "animations/stopAnimation.hpp"

#include "networking/network.hpp"
#include "networking/websocket.hpp"

#include "animator.hpp"
#include "fader.hpp"
#include "time.hpp"
#include "settings.hpp"

#include "debugging/logger.hpp"
#include "debugging/status.hpp"

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
  // real bar
  FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  // test board
  //FastLED.addLeds<APA102, 13, 32, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<APA102, 14, 32, BGR>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // TODO: find optimum value
  FastLED.setMaxPowerInMilliWatts(30000);


  Status.init();

  // these are all the animations the system knows
  Animator.addAnimation(new SinglePulseAnimation());
  Animator.addAnimation(new NoiseAnimation());
  Animator.addAnimation(new StroboAnimation());
  Animator.addAnimation(new FadeTextAnimation());
  Animator.addAnimation(new GlitchTextAnimation());
  Animator.addAnimation(new ScrollTextAnimation());
  Animator.addAnimation(new StaticTextAnimation());
  Animator.addAnimation(new StopAnimation());

  Serial.begin(115200);

  Network.startWifi();

  Status.setup();

  do
  {
    PrintLnInfo("Waiting for network..");
    delay(100);
  } while (!Network.networkIsConnected());

  PrintLnInfo("Network started!");

  JsonHandler.onAnimation(animationCallback);
  //JsonHandler.onStateChange(stateChangeCallback);

  // Udp.begin();
  //WebSocket.onStateChange(stateChangeCallback);
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
    if (Time.t12000ms)
    {
      WebSocket.cleanUp();
    }

    if (Time.t1000ms)
    {
      //stateChangeCallback();
    }
  } while (true);
}
