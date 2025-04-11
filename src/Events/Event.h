/**
 * @file Event.h
 * @author Owen McManus
 * @date 2025/4/11
 */

#pragma once

#include "../Utils/Keys.h"

#include <memory>

namespace OEngine {

enum class EventType { NONE = 0, KEYDOWN, KEYUP, MOUSE_BUTTON_DOWN, MOUSE_BUTTON_UP, QUIT };

class Event {
  public:
    virtual ~Event() = default;
    virtual EventType GetType() const = 0;
    virtual std::unique_ptr<Event> Clone() const = 0;
    bool Handled = false;
};

class KeyEvent : public Event {
  public:
    explicit KeyEvent(Key key);
    [[nodiscard]] Key GetKey() const;

  private:
    Key key;
};

class KeyDownEvent : public KeyEvent {
  public:
    explicit KeyDownEvent(Key key);
    [[nodiscard]] EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};

class KeyUpEvent : public KeyEvent {
  public:
    explicit KeyUpEvent(Key key);
    [[nodiscard]] EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};

class QuitEvent : public Event {
  public:
    QuitEvent() = default;
    [[nodiscard]] EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};
} // namespace OEngine
