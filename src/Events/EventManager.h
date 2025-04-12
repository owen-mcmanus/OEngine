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

template <typename EventKind> using EventListener = std::function<void(const EventKind&)>;
using GenericEventListener = std::pair<void*, std::function<void(const Event&)>>;

class EventManager {
  public:
    EventManager() = delete;
    static void HandleEvents();
    static void AddEvent(const Event& e);

    template <typename EventKind> static void AddListener(EventListener<EventKind>* listener) {
        auto wrapper = [listener](const Event& event) {
            (*listener)(static_cast<const EventKind&>(event));
        };
        auto key = std::type_index(typeid(EventKind));
        eventListeners[key].push_back({listener, wrapper});

        // if constexpr (std::is_same_v<EventKind, QuitEvent>) {
        //     quitEventListeners.push_back(listener);
        // }
    }

    template <typename EventKind> static void RemoveListener(EventListener<EventKind>* listener) {
        auto key = std::type_index(typeid(EventKind));
        auto it = eventListeners.find(key);
        if (it != eventListeners.end()) {
            auto& vec = it->second;
            std::erase_if(vec, [listener](auto& e) { return listener == e.first; });
        }
    }

  private:
    // static void DispatchGenericEvent(const Event& event);

    static std::queue<std::unique_ptr<Event>> eventQueue;
    // static std::vector<EventListener<QuitEvent>*> quitEventListeners;
    static std::unordered_map<std::type_index, std::vector<GenericEventListener>> eventListeners;
    static void HandleSDLEvents();
    static void DispatchEvent(Event& event);
};

} // namespace OEngine