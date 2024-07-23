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
#include "time.hpp"
#include "settings.hpp"

Settings globalSettings;

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
  Serial.print("Animation requested: ");
  Serial.println(animationName);

  for (auto animation : animations)
  {
    if (strcmp(animation->name(), animationName) == 0)
    {
      if (currentAnimation == animation)
      {
        Serial.println("Animation already active");
        break;
      }
      else if (currentAnimation != nullptr)
      {
        Serial.print("Stopping animation ");
        Serial.print(currentAnimation->name());
        Serial.println("..");
        currentAnimation->stop();
      }

      Serial.println("Starting animation..");
      animation->start();

      currentAnimation = animation;

      Time.interrupt();

      break;
    }
  }
}

void changeSettings(Settings newSettings)
{
  Serial.print("New setting: ");
  Serial.println(newSettings.text);
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
    Serial.println("Waiting for network..");
    delay(100);
  } while (!Network.ethernetIsConnected());

  WebSocket.onAnimation(changeAnimation);
  WebSocket.begin();
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
    ws.cleanupClients();
  }
}
