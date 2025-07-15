/**
 * @file Event.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "Event.h"

#include <iostream>

using namespace OEngine;

WindowResizeEvent::WindowResizeEvent(int width, int height) : width(width), height(height) {}

KeyEvent::KeyEvent(const Key::Keycode key) : key(key) {}

Key::Keycode KeyEvent::GetKey() const { return key; }

KeyDownEvent::KeyDownEvent(const Key::Keycode key) : KeyEvent(key) {}

KeyUpEvent::KeyUpEvent(Key::Keycode key) : KeyEvent(key) {}

MouseEvent::MouseEvent(float x, float y) : x(x), y(y) {};

float MouseEvent::GetX() const { return x; }

float MouseEvent::GetY() const { return y; }

MouseButtonEvent::MouseButtonEvent(float x, float y, Mouse::MouseButton button)
    : MouseEvent(x, y), button(button) {}

Mouse::MouseButton MouseButtonEvent::GetButton() const { return button; }

MouseButtonDownEvent::MouseButtonDownEvent(float x, float y, Mouse::MouseButton button, int clicks)
    : MouseButtonEvent(x, y, button), clicks(clicks) {}

MouseButtonUpEvent::MouseButtonUpEvent(float x, float y, Mouse::MouseButton button)
    : MouseButtonEvent(x, y, button) {}

MouseMovedEvent::MouseMovedEvent(float x, float y, float xrel, float yrel)
    : MouseEvent(x, y), xrel(xrel), yrel(yrel) {}

float MouseMovedEvent::GetXRel() const { return xrel; }

float MouseMovedEvent::GetYRel() const { return yrel; }

MouseScrolledEvent::MouseScrolledEvent(float x, float y, float scroll)
    : MouseEvent(x, y), scroll(scroll) {}

float MouseScrolledEvent::GetScroll() const { return scroll; }
