#include <Arduino.h>
#include <FastLED.h>
#include <vector>

/*
Animation
- name(): string
- start(setup): void
- stop(): void
- isActive(): bool
- loop(): void


- Animation: string
- Text: string
- Color1-5: hsv
- Speed: int
- Brightness: int
- Position: int
*/

struct Settings
{
  char *text;
  CRGB *colors;
  int speed;
  int brightness;
  int size;
};

Settings globalSettings;

class Animation
{
public:
  virtual char *name() = 0;
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual bool isActive() = 0;
  virtual void loop() = 0;
};

class TestAnimation : public Animation
{
public:
  TestAnimation() {

  }

  char *name()
  {
    return "Test";
  };
  void start()
  {
  }
  void stop()
  {
  }
  bool isActive()
  {
  }
  void loop()
  {
  }
};

std::vector<Animation *> animations = {
    new TestAnimation(),

};

Animation *currentAnimation = nullptr;

void setup()
{
  // websocket opzetten
}

void handleWebsocketMessage(uint8_t *data, uint8_t length)
{
  char *messageAction = new char[length];
  char *payload = new char[length];

  strncpy(messageAction, (char *)data, length);
  strncpy(payload, ((char *)data) + strlen(messageAction), length - strlen(messageAction));

  if (strcmp(messageAction, "updatetext") == 0)
  {
    delete globalSettings.text;
    globalSettings.text = payload;
  }

  for (auto animation : animations)
  {
    if (strcmp(animation->name(), messageAction) == 0)
    {
      if (currentAnimation != nullptr)
      {
        currentAnimation->stop();

        if (currentAnimation == animation)
        {
          currentAnimation = nullptr;
          break;
        }
      }

      animation->start();

      currentAnimation = animation;

      break;
    }
  }
}

void loop()
{
  if (currentAnimation != nullptr && currentAnimation->isActive())
  {
    currentAnimation->loop();
  }
}
