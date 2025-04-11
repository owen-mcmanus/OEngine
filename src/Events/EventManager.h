/**
 * @file EventManager.h
 * @author Owen McManus
 * @date 2025/4/11
 */

#pragma once
#include "Event.h"

#include <functional>
#include <memory>
#include <queue>
#include <vector>

namespace OEngine {

template <typename EventKind> using EventListener = std::function<void(const EventKind&)>;

class EventManager {
  public:
    EventManager() = delete;
    static void HandleEvents();
    static void AddEvent(const Event& e);

    template <typename EventKind> static void AddListener(EventListener<EventKind>* listener) {
        if constexpr (std::is_same_v<EventKind, QuitEvent>) {
            quitEventListeners.push_back(listener);
        }
    }

    template <typename EventKind> static void RemoveListener(EventListener<EventKind>* listener) {
        if constexpr (std::is_same_v<EventKind, QuitEvent>) {
            std::erase(quitEventListeners, listener);
        }
    }

  private:
    // static void DispatchGenericEvent(const Event& event);

    static std::queue<std::unique_ptr<Event>> eventQueue;
    static std::vector<EventListener<QuitEvent>*> quitEventListeners;
    static void HandleSDLEvents();
};

} // namespace OEngine