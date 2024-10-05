#include <Arduino.h>
#include <FastLED.h>
#include <WiFiNINA.h>
#include <stdio.h>
#include <setjmp.h>

#define LEDS 24

#include "leds.hpp"

#include "animation.hpp"

// tested animations
// #include "animations/stroboAnimation.hpp"
// #include "animations/fireAnimation.hpp"
// #include "animations/noiseAnimation.hpp"
#include "animations/stopAnimation.hpp"

#include "animations/singlePulseAnimation.hpp"
// #include "animations/doublePulseAnimation.hpp"

// #include "animations/singlePartialPulseAnimation.hpp"

// #include "animations/singleChaseAnimation.hpp"
// #include "animations/doubleChaseAnimation.hpp"

// expermental animations
// #include "animations/singleSteppedChaseAnimation.hpp"
// #include "animations/pongAnimation.hpp"

// /

#include "networking/network.hpp"
#include "networking/websocketServer.hpp"

#include "animator.hpp"
#include "time.hpp"
#include "settings.hpp"

#include "debugging/logger.hpp"
#include "debugging/status.hpp"

auto animationCallback = [](std::string animation)
{
  Animator.changeAnimation(animation);
};

void setup()
{
  FastLED.addLeds<WS2811, 4, GRB>(leds, LEDS).setCorrection(TypicalLEDStrip);

  Status.init();

  // these are all the animations the system knows
  Animator.addAnimation(new SinglePulseAnimation());
  // Animator.addAnimation(new DoublePulseAnimation());

  // Animator.addAnimation(new SinglePartialPulseAnimation());

  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());
  // Animator.addAnimation(new SingleChaseAnimation());

  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());
  // Animator.addAnimation(new DoubleChaseAnimation());

  // Animator.addAnimation(new SingleSteppedChaseAnimation());

  // Animator.addAnimation(new StroboAnimation());
  // Animator.addAnimation(new FireAnimation());
  // Animator.addAnimation(new NoiseAnimation());
  // Animator.addAnimation(new PongAnimation());

  Animator.addAnimation(new StopAnimation());

  Serial.begin(9600);

  Serial.println("HI");

  Network.startWiFi();

  Status.setup();

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

    WebSocket.loop();

  } while (true);
}
