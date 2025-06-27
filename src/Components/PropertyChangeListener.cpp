/**
 * @file PropertyChangeListener.cpp
 * @author Owen McManus
 * @date 2025/5/4
 */

#include "PropertyChangeListener.h"

#include "Events/EventManager.h"

using namespace OEngine;

PropertyChangedEvent::PropertyChangedEvent(
    void* owner,
    const std::string& name,
    std::any oldValue,
    std::any newValue)
    : owner(owner), name(name), oldValue(oldValue), newValue(newValue) {}

void PropertyChangeListener::Update(double deltaTime) {
    for (auto& w : watches) {
        std::any cur = w.grab();
        if (!w.equal(cur, w.prev)) {
            EventManager::AddEvent<PropertyChangedEvent>(w.owner, w.name, w.prev, cur);
            w.prev = std::move(cur);
        }
    }
}

void PropertyChangeListener::Clear() { watches.clear(); }
