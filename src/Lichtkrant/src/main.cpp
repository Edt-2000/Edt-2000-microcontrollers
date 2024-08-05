#include <Arduino.h>
#include <FastLED.h>
#include <AsyncWebSocket.h>
#include <vector>
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

#include "time.hpp"
#include "settings.hpp"

#include "debugging/logger.hpp"

// my demo board has led "strips" with 1 led
CRGB *leds = new CRGB[1];

// these are all the animations the system knows
std::vector<Animation *> animations = {
    new BlinkAnimation(),
    new StroboAnimation(),
};
// current animation that's active - can be null
Animation *currentAnimation = nullptr;

void changeAnimation(const char *animationName)
{
  PrintDebug("Animation requested: ");
  PrintLnDebug(animationName);

  for (auto animation : animations)
  {
    if (strcmp(animation->name(), animationName) == 0)
    {
      if (currentAnimation == animation)
      {
        PrintLnInfo("Animation already running..");
        break;
      }
      else if (currentAnimation != nullptr)
      {
        PrintDebug("Stopping animation ");
        PrintDebug(currentAnimation->name());
        PrintLnDebug("..");
        currentAnimation->stop();
      }

      PrintLnInfo("Starting animation..");
      animation->start();

      currentAnimation = animation;

      Time.interrupt();

      break;
    }
  }
}

void setup()
{
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

  //Udp.onAnimation(changeAnimation);
  //Udp.begin();
  WebSocket.onAnimation(changeAnimation);
  WebSocket.begin();

  PrintLnInfo("App started!");
}

// this buffer saves the start of the loop, which allows the time class
// to jump to, interrupting the animation loop
jmp_buf loop_jump_buffer;

void loop()
{
  setjmp(loop_jump_buffer);

  // copy animation pointer over to avoid race conditions
  auto animation = currentAnimation;
  if (animation != nullptr)
  {
    if (animation->isActive())
    {
      animation->loop();
    }
    else
    {
      // animation has finished
      currentAnimation = nullptr;
    }
  }

  Time.loop();

  // run maintenance logic
  if (Time.t1000ms) {
    WebSocket.cleanUp();
  }
}
