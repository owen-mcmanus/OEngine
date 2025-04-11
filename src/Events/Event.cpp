/**
 * @file Event.cpp
 * @author Owen McManus
 * @date 2025/4/11
 */

#include "Event.h"

#include <iostream>

using namespace OEngine;

KeyEvent::KeyEvent(const Key key) : key(key) {}

Key KeyEvent::GetKey() const { return key; }

KeyDownEvent::KeyDownEvent(const Key key) : KeyEvent(key) {}

EventType KeyDownEvent::GetType() const { return EventType::KEYDOWN; }

std::unique_ptr<Event> KeyDownEvent::Clone() const { return std::make_unique<KeyDownEvent>(*this); }

KeyUpEvent::KeyUpEvent(Key key) : KeyEvent(key) {}

EventType KeyUpEvent::GetType() const { return EventType::KEYUP; }

std::unique_ptr<Event> KeyUpEvent::Clone() const { return std::make_unique<KeyUpEvent>(*this); }

EventType QuitEvent::GetType() const { return EventType::QUIT; }

std::unique_ptr<Event> QuitEvent::Clone() const { return std::make_unique<QuitEvent>(*this); }