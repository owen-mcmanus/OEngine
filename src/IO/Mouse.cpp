/**
 * @file Mouse.cpp
 * @author Owen McManus
 * @date 2025/5/16
 */

#include "Mouse.h"
#include "../Events/Event.h"
#include "../Events/EventManager.h"
#include "AssetManager/TextureManager.h"

#include <SDL3/SDL.h>
#include <filesystem>
#include <olog.h>

using namespace OEngine;

enum class KeyState { RELEASED = 0, PRESSED };

static constexpr int NUMBER_OF_KEYS = 3;

static float scroll = 0;

std::vector<KeyState> mouseState(NUMBER_OF_KEYS, KeyState::RELEASED);
float x, y = 0;

EventListener<MouseButtonDownEvent> buttonDownListener = [](const MouseButtonDownEvent& e) {
    mouseState[static_cast<int>(e.GetButton()) - 1] = KeyState::PRESSED;
};

EventListener<MouseButtonUpEvent> buttonUpListener = [](const MouseButtonUpEvent& e) {
    mouseState[static_cast<int>(e.GetButton()) - 1] = KeyState::RELEASED;
};

EventListener<MouseMovedEvent> mouseMoveListener = [](const MouseMovedEvent& e) {
    x = e.GetX();
    y = e.GetY();
};
static bool isConnected = false;

void Mouse::Connect() {
    if (!isConnected) {
        isConnected = true;
        EventManager::AddListener<MouseButtonDownEvent>(&buttonDownListener);
        EventManager::AddListener<MouseButtonUpEvent>(&buttonUpListener);
        EventManager::AddListener<MouseMovedEvent>(&mouseMoveListener);
    }
}

void Mouse::Disconnect() {
    isConnected = false;
    EventManager::RemoveListener<MouseButtonDownEvent>(&buttonDownListener);
    EventManager::RemoveListener<MouseButtonUpEvent>(&buttonUpListener);
    EventManager::RemoveListener<MouseMovedEvent>(&mouseMoveListener);
    mouseState = std::vector<KeyState>(NUMBER_OF_KEYS, KeyState::RELEASED);
}

std::vector<Mouse::MouseButton> Mouse::GetPressed() {
    std::vector<Mouse::MouseButton> pressedButtons;

    if (mouseState[0] == KeyState::PRESSED) {
        pressedButtons.push_back(Mouse::MouseButton::LEFT);
    }
    if (mouseState[1] == KeyState::PRESSED) {
        pressedButtons.push_back(Mouse::MouseButton::MIDDLE);
    }
    if (mouseState[2] == KeyState::PRESSED) {
        pressedButtons.push_back(Mouse::MouseButton::RIGHT);
    }

    return pressedButtons;
}

bool Mouse::IsPressed(MouseButton key) {
    return mouseState[static_cast<int>(key) - 1] == KeyState::PRESSED;
}

float Mouse::GetX() {
    // float x1 = 0;
    // SDL_GetMouseState(&x1, nullptr);
    return x;
}

float Mouse::GetY() {
    // float y1 = 0;
    // SDL_GetMouseState(nullptr, &y1);
    return y;
}

// void Mouse::SetCursor(const std::filesystem::path& path) {
//     AssetManager::cursor_id id = AssetManager::CursorManager::LoadCursor(path);
//     SDL_Cursor* c = AssetManager::CursorManager::GetCursor(id);
//
//     SDL_Cursor* old_c = SDL_GetCursor();
//     SDL_SetCursor(c);
//     SDL_DestroyCursor(old_c);
// }

void Mouse::SetCursor(const std::filesystem::path& path) {
    AssetManager::surface_id surf_id = AssetManager::TextureManager::LoadSurface(path);
    SDL_Surface* s = AssetManager::TextureManager::GetSurface(surf_id);
    SDL_Cursor* c = SDL_CreateColorCursor(s, 0, 0);

    SDL_Cursor* old_c = SDL_GetCursor();
    SDL_SetCursor(c);
    SDL_DestroyCursor(old_c);
}

void Mouse::SetCursorDefault() {
    SDL_Cursor* old_c = SDL_GetCursor();
    SDL_Cursor* c = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
    SDL_SetCursor(c);
    SDL_DestroyCursor(old_c);
}

void Mouse::SetCursorPointer() {
    SDL_Cursor* old_c = SDL_GetCursor();
    SDL_Cursor* c = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
    SDL_SetCursor(c);
    SDL_DestroyCursor(old_c);
}