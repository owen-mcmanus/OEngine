/**
 * @file Keys.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "Keys.h"
#include <SDL3/SDL.h>

using namespace OEngine;

char Key::ToCharUppercase(Keycode key) {
    char c = static_cast<char>(key);
    if (c >= '0' && c <= '9') {
        return c;
    }

    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return 0;
}

char Key::ToCharLowercase(Keycode key) {
    char c = static_cast<char>(key);
    if (c >= '0' && c <= '9' || c >= 'a' && c <= 'z') {
        return c;
    }
    return 0;
}

Key::Keycode Key::SDLToKey(uint32_t sdlKey) { return static_cast<Keycode>(sdlKey); }
