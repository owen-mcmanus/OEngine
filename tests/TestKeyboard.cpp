#include "../src/Events/Event.h"
#include "../src/Events/EventManager.h"
#include "../src/IO/Keyboard.h"
#include <gtest/gtest.h>

using namespace OEngine;

class KeyboardTest : public ::testing::Test {
  protected:
    void SetUp() override { Keyboard::Connect(); }

    void TearDown() override { Keyboard::Disconnect(); }
};

TEST_F(KeyboardTest, KeyDownUpdatesStateToPressed) {
    KeyDownEvent event(Key::Keycode::A);
    EventManager::AddEvent(event);
    EventManager::HandleEvents();

    auto pressed = Keyboard::GetPressed();
    ASSERT_EQ(pressed.size(), 1);
    EXPECT_EQ(pressed[0], Key::Keycode::A);
}

TEST_F(KeyboardTest, KeyUpUpdatesStateToReleased) {
    KeyDownEvent downEvent(Key::Keycode::B);
    EventManager::AddEvent(downEvent);
    EventManager::HandleEvents();

    KeyUpEvent upEvent(Key::Keycode::B);
    EventManager::AddEvent(upEvent);
    EventManager::HandleEvents();

    auto pressed = Keyboard::GetPressed();
    EXPECT_TRUE(pressed.empty());
}

TEST_F(KeyboardTest, MultipleKeysPressedAndReleased) {
    KeyDownEvent downA(Key::Keycode::A);
    KeyDownEvent downB(Key::Keycode::B);
    EventManager::AddEvent(downA);
    EventManager::AddEvent(downB);
    EventManager::HandleEvents();

    auto pressed = Keyboard::GetPressed();
    EXPECT_EQ(pressed.size(), 2);
    EXPECT_NE(std::find(pressed.begin(), pressed.end(), Key::Keycode::A), pressed.end());
    EXPECT_NE(std::find(pressed.begin(), pressed.end(), Key::Keycode::B), pressed.end());

    KeyUpEvent upA(Key::Keycode::A);
    EventManager::AddEvent(upA);
    EventManager::HandleEvents();

    pressed = Keyboard::GetPressed();
    EXPECT_EQ(pressed.size(), 1);
    EXPECT_EQ(pressed[0], Key::Keycode::B);
}

TEST_F(KeyboardTest, ReturnsTrueWhenKeyIsPressed) {
    KeyDownEvent event(Key::Keycode::C);
    EventManager::AddEvent(event);
    EventManager::HandleEvents();

    EXPECT_TRUE(Keyboard::IsPressed(Key::Keycode::C));
}

TEST_F(KeyboardTest, ReturnsFalseWhenKeyIsReleased) {
    // Press and then release the key
    EventManager::AddEvent(KeyDownEvent(Key::Keycode::D));
    EventManager::AddEvent(KeyUpEvent(Key::Keycode::D));
    EventManager::HandleEvents();

    EXPECT_FALSE(Keyboard::IsPressed(Key::Keycode::D));
}

TEST_F(KeyboardTest, ReturnsFalseForNeverPressedKey) {
    EXPECT_FALSE(Keyboard::IsPressed(Key::Keycode::E));
}