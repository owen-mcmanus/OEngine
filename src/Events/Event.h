/**
 * @file Event.h
 * @author Owen McManus
 * @date 2025/4/11
 */

#pragma once

#include "../Utils/Keys.h"

#include <memory>

namespace OEngine {

/**
 * @brief Enumeration of supported event types.
 */
enum class EventType { NONE = 0, KEYDOWN, KEYUP, MOUSE_BUTTON_DOWN, MOUSE_BUTTON_UP, QUIT, CUSTOM };

/**
 * @brief Abstract base class for all events.
 */
class Event {
  public:
    virtual ~Event() = default;

    /**
     * @brief Retrieves the event type.
     * @return EventType The type of the event.
     */
    virtual EventType GetType() const = 0;

    /**
     * @brief Clones the event object.
     * @return A unique_ptr to a copy of this event.
     */
    virtual std::unique_ptr<Event> Clone() const = 0;

    /// Indicates whether the event has been handled.
    bool Handled = false;
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
    [[nodiscard]] EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};

/**
 * @brief Represents a key up (released) event.
 */
class KeyUpEvent : public KeyEvent {
  public:
    explicit KeyUpEvent(Key::Keycode key);
    [[nodiscard]] EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};

/**
 * @brief Represents a quit event (e.g., closing the window).
 */
class QuitEvent : public Event {
  public:
    QuitEvent() = default;
    [[nodiscard]] EventType GetType() const override;
    [[nodiscard]] std::unique_ptr<Event> Clone() const override;
};
} // namespace OEngine
