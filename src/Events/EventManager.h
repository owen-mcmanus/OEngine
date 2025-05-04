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
#include <typeindex>
#include <vector>

namespace OEngine {

/**
 * @brief Function signature for event listeners.
 *
 * @tparam EventKind The specific type of event being handled.
 */
template <typename EventKind> using EventListener = std::function<void(const EventKind&)>;

/**
 * @brief Internal representation of a generic event listener wrapper.
 *
 * Holds a void* pointer to the original listener function and a wrapped version
 * that operates on the base Event type for dispatching.
 */
using GenericEventListener = std::pair<void*, std::function<void(const Event&)>>;

/**
 * @brief Static class that manages events and listeners.
 */
class EventManager {
  public:
    EventManager() = delete;

    /**
     * @brief Polls SDL events and dispatches all queued events to listeners.
     */
    static void HandleEvents();

    /**
     * @brief Adds a new event to the event queue.
     *
     * @param e The event to enqueue.
     */
    template <typename T, typename... Args> static void AddEvent(Args&&... args) {
        eventQueue.push(std::make_unique<T>(std::forward<Args>(args)...));
    }

    /**
     * @brief Registers a listener for a specific type of event.
     *
     * @tparam EventKind The specific event type.
     * @param listener A pointer to the listener function.
     */
    template <typename EventKind> static void AddListener(EventListener<EventKind>* listener) {
        auto wrapper = [listener](const Event& event) {
            (*listener)(static_cast<const EventKind&>(event));
        };
        auto key = std::type_index(typeid(EventKind));
        eventListeners[key].push_back({listener, wrapper});
    }

    /**
     * @brief Removes a listener for a specific type of event.
     *
     * @tparam EventKind The specific event type.
     * @param listener A pointer to the listener function to remove.
     */
    template <typename EventKind> static void RemoveListener(EventListener<EventKind>* listener) {
        auto key = std::type_index(typeid(EventKind));
        auto it = eventListeners.find(key);
        if (it != eventListeners.end()) {
            auto& vec = it->second;
            std::erase_if(vec, [listener](auto& e) { return listener == e.first; });
        }
    }

    static void DispatchEvent(Event& event);

  private:
    static std::queue<std::unique_ptr<Event>> eventQueue;
    static std::unordered_map<std::type_index, std::vector<GenericEventListener>> eventListeners;
    static void HandleSDLEvents();
};

} // namespace OEngine