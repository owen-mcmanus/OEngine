/**
 * @file EventManager.cpp
 * @author Owen McManus
 * @date 2025/4/11
 */

#include "EventManager.h"

#include "Event.h"

#include <SDL3/SDL.h>

using namespace OEngine;

std::queue<std::unique_ptr<Event>> EventManager::eventQueue;
std::vector<EventListener<QuitEvent>*> EventManager::quitEventListeners;

void EventManager::HandleEvents() {
    HandleSDLEvents();

    while (!eventQueue.empty()) {
        Event* e_ptr = eventQueue.front().get();
        if (!e_ptr) {
            eventQueue.pop();
            continue;
        }
        Event& event = *e_ptr;
        if (event.GetType() == EventType::QUIT) {
            auto& q = dynamic_cast<QuitEvent&>(event);
            for (auto listener : EventManager::quitEventListeners) {
                if (listener)
                    (*listener)(q);
            }
        }
        eventQueue.pop();
    }
}

void EventManager::AddEvent(const Event& e) { eventQueue.emplace(e.Clone()); }

void EventManager::HandleSDLEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) { // TODO: consider SDL_WaitEvent
        switch (sdlEvent.type) {
        case SDL_EVENT_QUIT: {
            AddEvent(QuitEvent());
            break;
        }
        default:
            break;
        }
    }
}
