#include <StateMachine.h>
#include <State.h>
#include <unity.h>

void test_statemachine_starts_with_begin()
{
    App::StateMachine statemachine;
    TEST_ASSERT_EQUAL(App::State::begin, statemachine.current());
}

void test_statemachine_flow()
{
    App::StateMachine statemachine;
    TEST_ASSERT_EQUAL(App::State::begin, statemachine.current());
    statemachine.step();
    TEST_ASSERT_EQUAL(App::State::networking, statemachine.current());
    statemachine.step();
    TEST_ASSERT_EQUAL(App::State::specifics, statemachine.current());
    statemachine.step();
    TEST_ASSERT_EQUAL(App::State::initialized, statemachine.current());
    statemachine.step();
    TEST_ASSERT_EQUAL(App::State::run, statemachine.current());
}

void test_statemachine_runs_when_is_running()
{
    App::StateMachine statemachine;
    statemachine.step();
    statemachine.step();
    statemachine.step();
    statemachine.step();
    TEST_ASSERT_EQUAL(App::State::run, statemachine.current());
    statemachine.step();
    TEST_ASSERT_EQUAL(App::State::run, statemachine.current());
}

void process()
{
    UNITY_BEGIN();

    RUN_TEST(test_statemachine_starts_with_begin);
    RUN_TEST(test_statemachine_flow);
    RUN_TEST(test_statemachine_runs_when_is_running);

    UNITY_END();
}

#ifdef ARDUINO
#include <Arduino.h>

void setup() {
    delay(3000);
    process();
}
void loop() {
    delay(1);
}

#else

int main(int argc, char **argv) {
    process();
}

#endif