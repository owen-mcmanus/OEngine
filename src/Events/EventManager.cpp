/**
 * @file EventManager.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "EventManager.h"

#include "../../cmake-build-debug-coverage/_deps/olog-src/include/olog.h"
#include "Event.h"

#include <SDL3/SDL.h>
#include <cmath>
#include <iostream>

using namespace OEngine;

std::queue<std::unique_ptr<Event>> EventManager::eventQueue;
std::unordered_map<std::type_index, std::vector<GenericEventListener>> EventManager::eventListeners;

void EventManager::HandleEvents() {
    HandleSDLEvents();

    while (!eventQueue.empty()) {
        Event* e_ptr = eventQueue.front().get();
        if (!e_ptr) {
            eventQueue.pop();
            continue;
        }
        DispatchEvent(*e_ptr);
        eventQueue.pop();
    }
}

void EventManager::HandleSDLEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) { // TODO: consider SDL_WaitEvent
        switch (sdlEvent.type) {
        case SDL_EVENT_QUIT: {
            AddEvent<QuitEvent>();
            break;
        }
        case SDL_EVENT_KEY_DOWN: {
            AddEvent<KeyDownEvent>(Key::SDLToKey(sdlEvent.key.key));
            break;
        }
        case SDL_EVENT_KEY_UP: {
            AddEvent<KeyUpEvent>(Key::SDLToKey(sdlEvent.key.key));
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_UP: {
            AddEvent<MouseButtonUpEvent>(
                sdlEvent.button.x, sdlEvent.button.y,
                static_cast<Mouse::MouseButton>(sdlEvent.button.button));
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            AddEvent<MouseButtonDownEvent>(
                sdlEvent.button.x, sdlEvent.button.y,
                static_cast<Mouse::MouseButton>(sdlEvent.button.button), sdlEvent.button.clicks);
            break;
        }
        case SDL_EVENT_MOUSE_MOTION: {
            AddEvent<MouseMovedEvent>(
                sdlEvent.motion.x, sdlEvent.motion.y, sdlEvent.motion.xrel, sdlEvent.motion.yrel);
            break;
        }
        case SDL_EVENT_MOUSE_WHEEL: {
            AddEvent<MouseScrolledEvent>(
                sdlEvent.wheel.mouse_x, sdlEvent.wheel.mouse_y, sdlEvent.wheel.y);
            break;
        }
        default:
            break;
        }
    }
}

void EventManager::DispatchEvent(Event& event) {
    auto key = std::type_index(typeid(event));
    auto it = eventListeners.find(key);
    if (it != eventListeners.end()) {
        for (auto& [id, listener] : it->second) {
            listener(event);
        }
    }
}
