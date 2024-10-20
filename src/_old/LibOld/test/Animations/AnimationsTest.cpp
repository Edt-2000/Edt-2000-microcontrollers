#include <unity.h>
#include <Animations.h>

void addAnimationTest()
{
    Animations::Animations subject;

    auto animation = Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12);

    subject.addAnimation(animation);

    TEST_ASSERT_EQUAL(1, subject.activeAnimations());
}

void addAndRemoveAnimationTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));
    subject.removeAnimation(0);

    TEST_ASSERT_EQUAL(0, subject.activeAnimations());
}

void addAndRemoveAnimationByTypeTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));
    subject.removeAnimation(Animations::AnimationType::Strobo);

    TEST_ASSERT_EQUAL(0, subject.activeAnimations());
}

void addAndRemoveAnimationByElementTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));

    for (auto &animation : subject.animations)
    {
        subject.removeAnimation(animation);
    }

    TEST_ASSERT_EQUAL(0, subject.activeAnimations());
}

void addAndIncorrectRemoveAnimationTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));
    subject.removeAnimation(Animations::AnimationType::ChaseStill);

    TEST_ASSERT_EQUAL(1, subject.activeAnimations());
}

void addMultipeAndRemoveAnimationTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(2, 3, 4), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(3, 4, 5), 12, 12));
    subject.removeAnimation(1);

    TEST_ASSERT_EQUAL(2, subject.activeAnimations());

    auto iterator = subject.animations.begin();

    TEST_ASSERT_EQUAL(1, iterator++->color.h);
    TEST_ASSERT_EQUAL(3, iterator++->color.h);
}

void addNumerousAndRemoveAnimationTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(2, 3, 4), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(3, 4, 5), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(4, 5, 6), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(5, 6, 7), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(6, 7, 8), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(7, 8, 9), 12, 12));
    subject.removeAnimation(1);

    TEST_ASSERT_EQUAL(6, subject.activeAnimations());

    auto iterator = subject.animations.begin();

    TEST_ASSERT_EQUAL(1, iterator++->color.h);
    TEST_ASSERT_EQUAL(3, iterator++->color.h);
    TEST_ASSERT_EQUAL(4, iterator++->color.h);
    TEST_ASSERT_EQUAL(5, iterator++->color.h);
    TEST_ASSERT_EQUAL(6, iterator++->color.h);
    TEST_ASSERT_EQUAL(7, iterator++->color.h);
}

void addMultipeAndRemoveAllAnimationTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(1, 2, 3), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(2, 3, 4), 12, 12));
    subject.addAnimation(Animations::Animation(Animations::AnimationType::Strobo, CHSV(3, 4, 5), 12, 12));
    subject.resetAnimations();

    TEST_ASSERT_EQUAL(0, subject.activeAnimations());
}

void updateAnimationTest()
{
    Animations::Animations subject;

    subject.addAnimation(Animations::Animation(Animations::AnimationType::ChaseStill, CHSV(1, 2, 3), 12, 0));
    TEST_ASSERT_EQUAL(0, subject.animations.front().state);
    TEST_ASSERT_EQUAL(1, subject.activeAnimations());

    subject.getAnimation(Animations::AnimationType::ChaseStill)->state += 1;
    TEST_ASSERT_EQUAL(1, subject.animations.front().state);
    TEST_ASSERT_EQUAL(1, subject.activeAnimations());

    subject.getAnimation(Animations::AnimationType::ChaseStill)->state += 1;
    TEST_ASSERT_EQUAL(2, subject.animations.front().state);
    TEST_ASSERT_EQUAL(1, subject.activeAnimations());
}

void getNonExistingAnimationTest()
{
    Animations::Animations subject;

    TEST_ASSERT_EQUAL(0, subject.activeAnimations());
    TEST_ASSERT_EQUAL(nullptr, subject.getAnimation(Animations::AnimationType::ChaseStill));
}

void process()
{
    UNITY_BEGIN();
    RUN_TEST(addAnimationTest);
    RUN_TEST(addAndRemoveAnimationTest);
    RUN_TEST(addAndRemoveAnimationByTypeTest);
    RUN_TEST(addAndRemoveAnimationByElementTest);
    RUN_TEST(addAndIncorrectRemoveAnimationTest);
    RUN_TEST(addMultipeAndRemoveAnimationTest);
    RUN_TEST(addNumerousAndRemoveAnimationTest);
    RUN_TEST(addMultipeAndRemoveAllAnimationTest);
    RUN_TEST(updateAnimationTest);
    RUN_TEST(getNonExistingAnimationTest);

    UNITY_END();
}

#ifdef ARDUINO

#include <Arduino.h>
void setup()
{
    delay(4000);

    process();
}

void loop()
{
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(500);
}

#else

int main(int argc, char **argv)
{
    process();
    return 0;
}

#endif