/**
 * @file Event.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "Event.h"

#include <iostream>

using namespace OEngine;

KeyEvent::KeyEvent(const Key::Keycode key) : key(key) {}

Key::Keycode KeyEvent::GetKey() const { return key; }

KeyDownEvent::KeyDownEvent(const Key::Keycode key) : KeyEvent(key) {}

EventType KeyDownEvent::GetType() const { return EventType::KEYDOWN; }

std::unique_ptr<Event> KeyDownEvent::Clone() const { return std::make_unique<KeyDownEvent>(*this); }

KeyUpEvent::KeyUpEvent(Key::Keycode key) : KeyEvent(key) {}

EventType KeyUpEvent::GetType() const { return EventType::KEYUP; }

std::unique_ptr<Event> KeyUpEvent::Clone() const { return std::make_unique<KeyUpEvent>(*this); }

EventType QuitEvent::GetType() const { return EventType::QUIT; }

std::unique_ptr<Event> QuitEvent::Clone() const { return std::make_unique<QuitEvent>(*this); }

MouseEvent::MouseEvent(float x, float y) : x(x), y(y) {};

float MouseEvent::GetX() const { return x; }

float MouseEvent::GetY() const { return y; }

MouseButtonEvent::MouseButtonEvent(float x, float y, Mouse::MouseButton button)
    : MouseEvent(x, y), button(button) {}

Mouse::MouseButton MouseButtonEvent::GetButton() const { return button; }

MouseButtonDownEvent::MouseButtonDownEvent(float x, float y, Mouse::MouseButton button, int clicks)
    : MouseButtonEvent(x, y, button), clicks(clicks) {}

EventType MouseButtonDownEvent::GetType() const { return EventType::MOUSE_BUTTON_DOWN; }

std::unique_ptr<Event> MouseButtonDownEvent::Clone() const {
    return std::make_unique<MouseButtonDownEvent>(*this);
}

MouseButtonUpEvent::MouseButtonUpEvent(float x, float y, Mouse::MouseButton button)
    : MouseButtonEvent(x, y, button) {}

EventType MouseButtonUpEvent::GetType() const { return EventType::MOUSE_BUTTON_UP; }

std::unique_ptr<Event> MouseButtonUpEvent::Clone() const {
    return std::make_unique<MouseButtonUpEvent>(*this);
}

MouseMovedEvent::MouseMovedEvent(float x, float y, float xrel, float yrel)
    : MouseEvent(x, y), xrel(xrel), yrel(yrel) {}

EventType MouseMovedEvent::GetType() const { return EventType::MOUSE_MOTION; }

std::unique_ptr<Event> MouseMovedEvent::Clone() const {
    return std::make_unique<MouseMovedEvent>(*this);
}

float MouseMovedEvent::GetXRel() const { return xrel; }

float MouseMovedEvent::GetYRel() const { return yrel; }

MouseScrolledEvent::MouseScrolledEvent(float x, float y, float scroll)
    : MouseEvent(x, y), scroll(scroll) {}

EventType MouseScrolledEvent::GetType() const { return EventType::MOUSE_SCROLL; }

std::unique_ptr<Event> MouseScrolledEvent::Clone() const {
    return std::make_unique<MouseScrolledEvent>(*this);
}

float MouseScrolledEvent::GetScroll() const { return scroll; }
