/**
 * @file Keyboard.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "Keyboard.h"
#include "../Events/EventManager.h"

#include <unordered_map>

using namespace OEngine;

enum class KeyState { RELEASED, PRESSED };

static constexpr int NUMBER_OF_KEYS = 104;

static std::unordered_map<Key::Keycode, KeyState> keyboardState;

EventListener<KeyDownEvent> keyDownListener = [](const KeyDownEvent& e) {
    keyboardState[e.GetKey()] = KeyState::PRESSED;
};

EventListener<KeyUpEvent> keyUpListener = [](const KeyUpEvent& e) {
    keyboardState[e.GetKey()] = KeyState::RELEASED;
};

void Keyboard::Connect() {
    EventManager::AddListener<KeyDownEvent>(&keyDownListener);
    EventManager::AddListener<KeyUpEvent>(&keyUpListener);
    keyboardState.reserve(NUMBER_OF_KEYS);
}

void Keyboard::Disconnect() {
    EventManager::RemoveListener<KeyDownEvent>(&keyDownListener);
    EventManager::RemoveListener<KeyUpEvent>(&keyUpListener);
    keyboardState.clear();
}

std::vector<Key::Keycode> Keyboard::GetPressed() {
    std::vector<Key::Keycode> pressedKeys;

    for (const auto& [key, state] : keyboardState) {
        if (state == KeyState::PRESSED) {
            pressedKeys.push_back(key);
        }
    }

    return pressedKeys;
}

bool Keyboard::IsPressed(const Key::Keycode key) { return keyboardState[key] == KeyState::PRESSED; }
