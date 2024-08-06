#include <Arduino.h>
#include <FastLED.h>
#include <AsyncWebSocket.h>
#include <Wifi.h>
#include <ETH.h>
#include <stdio.h>
#include <setjmp.h>

#include "animation.hpp"
#include "animations/allPulseAnimation.hpp"
#include "animations/allSolidAnimation.hpp"
#include "animations/allSparkleAnimation.hpp"
#include "animations/glowAnimation.hpp"
#include "animations/singlePulseAnimation.hpp"
#include "animations/stroboAnimation.hpp"

#include "animations/stopAnimation.hpp"

#include "networking/ethernet.hpp"
#include "networking/websocket.hpp"
// #include "networking/udp.hpp"

#include "animator.hpp"
#include "time.hpp"
#include "settings.hpp"

#include "debugging/logger.hpp"
#include "debugging/status.hpp"

// my demo board has led "strips" with 1 led
CRGB *led1 = new CRGB[1];
CRGB *led2 = new CRGB[1];

auto animationCallback = [](std::string animation)
{
  Animator.changeAnimation(animation);
};

void setup()
{
  FastLED.addLeds<APA102, 13, 32, BGR, DATA_RATE_KHZ(500)>(led1, 1).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<APA102, 14, 32, BGR, DATA_RATE_KHZ(500)>(led2, 1).setCorrection(TypicalLEDStrip);

  Status.init();

  // these are all the animations the system knows
  Animator.addAnimation(new AllPulseAnimation());
  Animator.addAnimation(new AllSolidAnimation());
  Animator.addAnimation(new AllSparkleAnimation());

  Animator.addAnimation(new GlowAnimation(0));
  Animator.addAnimation(new GlowAnimation(1));

  Animator.addAnimation(new SinglePulseAnimation());

  Animator.addAnimation(new StroboAnimation());

  Animator.addAnimation(new StopAnimation());

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

  // Udp.begin();
  WebSocket.begin();

  PrintLnInfo("App started!");

  Status.allOk();
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
    if (Time.t12000ms)
    {
      WebSocket.cleanUp();
    }
  } while (true);
}
