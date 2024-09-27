#include <Arduino.h>
#include <FastLED.h>
#include <Wifi.h>
#include <ETH.h>
#include <stdio.h>
#include <setjmp.h>

#include "leds.hpp"

#include "animation.hpp"

#define SERVER

// tested animations
#include "animations/stroboAnimation.hpp"
#include "animations/stopAnimation.hpp"

#include "animations/allSingleAnimation.hpp"
#include "animations/allDoubleAnimation.hpp"

#include "animations/oneSingleAnimation.hpp"

#include "animations/partialSingleAnimation.hpp"

#include "animations/allSingleChaseAnimation.hpp"
#include "animations/allDoubleChaseAnimation.hpp"

// expermental animations
// /

#include "networking/ethernet.hpp"
#ifdef SERVER
#include "networking/websocketServer.hpp"
#else
#include "networking/websocketClient.hpp"
#endif

#include "animator.hpp"
#include "time.hpp"
#include "settings.hpp"
#include "fastLedTask.hpp"

#include "debugging/logger.hpp"
#include "debugging/status.hpp"

auto animationCallback = [](std::string animation)
{
  Animator.changeAnimation(animation);
};

void setup()
{
  FastLED.addLeds<APA102, 16, 32, BGR, DATA_RATE_KHZ(500)>(leds0, 59).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 13, 32, BGR, DATA_RATE_KHZ(500)>(leds1, 59).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 14, 32, BGR, DATA_RATE_KHZ(500)>(leds2, 59).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 15, 32, BGR, DATA_RATE_KHZ(500)>(leds3, 59).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 5, 32, BGR, DATA_RATE_KHZ(500)>(leds4, 59).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 3, 32, BGR, DATA_RATE_KHZ(500)>(leds5, 59).setCorrection(TypicalLEDStrip); // 3 or 4?
  FastLED.addLeds<APA102, 4, 32, BGR, DATA_RATE_KHZ(500)>(leds6, 59).setCorrection(TypicalLEDStrip); // 4 or 3?
  FastLED.addLeds<APA102, 2, 32, BGR, DATA_RATE_KHZ(500)>(leds7, 59).setCorrection(TypicalLEDStrip);

  xTaskCreate(&fastLedTask, "OSC", 5120, NULL, 1, NULL);

  Status.init();

  // these are all the animations the system knows
  Animator.addAnimation(new AllSingleAnimation());
  Animator.addAnimation(new AllDoubleAnimation());

  Animator.addAnimation(new PartialSingleAnimation());

  Animator.addAnimation(new OneSingleAnimation());

  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());
  Animator.addAnimation(new AllSingleChaseAnimation());

  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());
  Animator.addAnimation(new AllDoubleChaseAnimation());

  Animator.addAnimation(new StopAnimation());
  Animator.addAnimation(new StroboAnimation());

  Serial.begin(115200);

  Network.startEthernet();

  Status.setup();

  do
  {
    PrintLnInfo("Waiting for network..");
    delay(100);
  } while (!Network.networkIsConnected());

  PrintLnInfo("Network started!");

  JsonHandler.onAnimation(animationCallback);

  WebSocket.begin();

  PrintLnInfo("App started!");

  Time.setup();
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

#ifdef DEBUG
    if (Time.t100ms)
    {
      WebSocket.send(String(Time.ms));
    }
    if (Time.t1000ms)
    {
      WebSocket.send("=== 1s");
    }
    if (Time.t12000ms)
    {
      WebSocket.send("================== 12s");
    }
#endif

#ifdef SERVER
    if (Time.t12000ms)
    {
      WebSocket.cleanUp();
    }
#endif

  } while (true);
}
