/**
 * @file TextInput.cpp
 * @author Owen McManus
 * @date 2025/5/16
 */

#include "TextInput.h"
#include "../Events/Event.h"
#include "../Events/EventManager.h"
#include "Core/Window.h"

#include <SDL3/SDL_keyboard.h>

using namespace OEngine;

static bool isConnected = false;
std::string inputText = "";

EventListener<TextInputEvent> textListener = [](const TextInputEvent& e) { inputText += e.text; };
EventListener<KeyDownEvent> backspaceListener = [](const KeyDownEvent& e) {
    if (e.GetKey() == Key::Keycode::BACKSPACE && inputText.length() > 0) {
        inputText.pop_back();
    }
};

void TextInput::Connect() {
    if (!isConnected) {
        isConnected = true;
        inputText = "";
        SDL_StartTextInput(Window::GetSDLWindow());
        EventManager::AddListener<TextInputEvent>(&textListener);
        EventManager::AddListener<KeyDownEvent>(&backspaceListener);
    }
}

void TextInput::Disconnect() {
    isConnected = false;
    inputText = "";
    SDL_StopTextInput(Window::GetSDLWindow());
    EventManager::RemoveListener<TextInputEvent>(&textListener);
    EventManager::RemoveListener<KeyDownEvent>(&backspaceListener);
}

std::string TextInput::GetText() { return inputText; }
