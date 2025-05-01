#include "../src/Events/Event.h"
#include "../src/Events/EventManager.h"
#include "../src/IO/Mouse.h"
#include <gtest/gtest.h>

using namespace OEngine;

class MouseTest : public ::testing::Test {
  protected:
    void SetUp() override { Mouse::Connect(); }

    void TearDown() override { Mouse::Disconnect(); }

    void PressButton(Mouse::MouseButton button) {
        EventManager::AddEvent<MouseButtonDownEvent>(0, 0, button, 1);
        EventManager::HandleEvents();
    }

    void ReleaseButton(Mouse::MouseButton button) {
        EventManager::AddEvent<MouseButtonUpEvent>(0, 0, button);
        EventManager::HandleEvents();
    }
};

TEST_F(MouseTest, InitiallyNoButtonsPressed) {
    EXPECT_FALSE(Mouse::IsPressed(Mouse::MouseButton::LEFT));
    EXPECT_FALSE(Mouse::IsPressed(Mouse::MouseButton::MIDDLE));
    EXPECT_FALSE(Mouse::IsPressed(Mouse::MouseButton::RIGHT));
    EXPECT_TRUE(Mouse::GetPressed().empty());
}

TEST_F(MouseTest, ButtonPressRegistersCorrectly) {
    PressButton(Mouse::MouseButton::LEFT);
    EXPECT_TRUE(Mouse::IsPressed(Mouse::MouseButton::LEFT));
    EXPECT_EQ(Mouse::GetPressed(), std::vector<Mouse::MouseButton>{Mouse::MouseButton::LEFT});

    PressButton(Mouse::MouseButton::RIGHT);
    EXPECT_TRUE(Mouse::IsPressed(Mouse::MouseButton::RIGHT));
    auto pressed = Mouse::GetPressed();
    EXPECT_NE(std::find(pressed.begin(), pressed.end(), Mouse::MouseButton::LEFT), pressed.end());
    EXPECT_NE(std::find(pressed.begin(), pressed.end(), Mouse::MouseButton::RIGHT), pressed.end());
}

TEST_F(MouseTest, ButtonReleaseUnregistersCorrectly) {
    PressButton(Mouse::MouseButton::LEFT);
    PressButton(Mouse::MouseButton::MIDDLE);
    ReleaseButton(Mouse::MouseButton::LEFT);

    EXPECT_FALSE(Mouse::IsPressed(Mouse::MouseButton::LEFT));
    EXPECT_TRUE(Mouse::IsPressed(Mouse::MouseButton::MIDDLE));

    auto pressed = Mouse::GetPressed();
    EXPECT_EQ(pressed.size(), 1);
    EXPECT_EQ(pressed[0], Mouse::MouseButton::MIDDLE);
}

TEST_F(MouseTest, MousePosition) {
    EventManager::AddEvent<MouseMovedEvent>(200, 100, 0, 0);
    EventManager::HandleEvents();

    EXPECT_EQ(Mouse::GetX(), 200);
    EXPECT_EQ(Mouse::GetY(), 100);
}