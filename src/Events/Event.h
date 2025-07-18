/**
 * @file Event.h
 * @author Owen McManus
 * @date 2025/4/11
 */

#pragma once

#include "../IO/Mouse.h"
#include "../Utils/Keys.h"

#include <memory>

namespace OEngine {

/**
 * @brief Enumeration of supported event types.
 */
// enum class EventType {
//     NONE = 0,
//     KEYDOWN,
//     KEYUP,
//     MOUSE_BUTTON_DOWN,
//     MOUSE_BUTTON_UP,
//     MOUSE_MOTION,
//     MOUSE_SCROLL,
//     QUIT,
//     CUSTOM
// };

/**
 * @brief Abstract base class for all events.
 */
class Event {
  public:
    virtual ~Event() = default;

    /// Indicates whether the event has been handled.
    bool Handled = false;
};

class WindowResizeEvent : public Event {
  public:
    explicit WindowResizeEvent(int width, int height);
    int width;
    int height;
};

/**
 * @brief Base class for all keyboard-related events.
 */
class KeyEvent : public Event {
  public:
    /**
     * @brief Constructs a new KeyEvent with the given key.
     * @param key The key involved in the event.
     */
    explicit KeyEvent(Key::Keycode key);

    /**
     * @brief Returns the key associated with this event.
     * @return Key The key involved.
     */
    [[nodiscard]] Key::Keycode GetKey() const;

  private:
    Key::Keycode key;
};

/**
 * @brief Represents a key down (pressed) event.
 */
class KeyDownEvent : public KeyEvent {
  public:
    explicit KeyDownEvent(Key::Keycode key);
};

/**
 * @brief Represents a key up (released) event.
 */
class KeyUpEvent : public KeyEvent {
  public:
    explicit KeyUpEvent(Key::Keycode key);
};

class TextInputEvent : public Event {
  public:
    explicit TextInputEvent(const std::string& text) : text(text) {};
    std::string text;
};

/**
 * @brief Represents a quit event (e.g., closing the window).
 */
class QuitEvent : public Event {
  public:
    QuitEvent() = default;
};

/**
 * @brief Base class for all mouse related events.
 */
class MouseEvent : public Event {
  public:
    explicit MouseEvent(float x, float y);
    [[nodiscard]] float GetX() const;
    [[nodiscard]] float GetY() const;

  private:
    float x;
    float y;
};

/**
 * @brief Base class for  a mouse button state change
 */
class MouseButtonEvent : public MouseEvent {
  public:
    explicit MouseButtonEvent(float x, float y, Mouse::MouseButton button);
    [[nodiscard]] Mouse::MouseButton GetButton() const;

  private:
    Mouse::MouseButton button;
};

/**
 * @brief Represents a mouse button press
 */
class MouseButtonDownEvent : public MouseButtonEvent {
  public:
    explicit MouseButtonDownEvent(float x, float y, Mouse::MouseButton button, int clicks);

  private:
    int clicks;
};

/**
 * @brief Represents a mouse button release
 */
class MouseButtonUpEvent : public MouseButtonEvent {
  public:
    explicit MouseButtonUpEvent(float x, float y, Mouse::MouseButton button);
};

class MouseMovedEvent : public MouseEvent {
  public:
    MouseMovedEvent(float x, float y, float xrel, float yrel);
    [[nodiscard]] float GetXRel() const;
    [[nodiscard]] float GetYRel() const;

  private:
    float xrel;
    float yrel;
};

class MouseScrolledEvent : public MouseEvent {
  public:
    MouseScrolledEvent(float x, float y, float scroll);
    [[nodiscard]] float GetScroll() const;

  private:
    float scroll;
};
} // namespace OEngine
