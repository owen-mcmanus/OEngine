/**
 * @file PropertyChangeListener.h
 * @author Owen McManus
 * @date 2025/5/4
 */

#pragma once
#include "Component.h"
#include "Events/Event.h"

#include <any>
#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace OEngine {
class PropertyChangedEvent : public Event {
  public:
    PropertyChangedEvent(
        void* owner,
        const std::string& name,
        std::any oldValue,
        std::any newValue);
    void* owner;
    std::string name;
    std::any oldValue;
    std::any newValue;
};

class PropertyChangeListener : public Component {
  public:
    PropertyChangeListener() = default;
    ~PropertyChangeListener() override = default;
    void Update(double deltaTime) override;

    template <typename T> void Watch(const T& var, std::string name, void* ownerPtr = nullptr) {
        WatchEntry e;
        e.name = std::move(name);
        e.owner = ownerPtr;
        e.prev = var;

        const T* addr = &var;
        e.grab = [addr]() -> std::any { return *addr; };

        e.equal = [](const std::any& a, const std::any& b) -> bool {
            return std::any_cast<const T&>(a) == std::any_cast<const T&>(b);
        };

        watches.push_back(std::move(e));
    }

    void Clear();

  private:
    struct WatchEntry {
        std::string name;
        void* owner{};
        std::function<std::any()> grab;
        std::function<bool(const std::any&, const std::any&)> equal;
        std::any prev;
    };

    std::vector<WatchEntry> watches;
};
} // namespace OEngine
