/**
 * @file FontManager.cpp
 * @author Owen McManus
 * @date 2025/5/18
 */

#include "FontManager.h"

#include "Utils/SDLDeleter.h"

#include <iostream>
#include <olog.h>
#include <stdexcept>

using namespace OEngine::AssetManager;

std::unordered_map<font_id, TTF_Font*> FontManager::fontCache;
std::unordered_map<std::string, font_id> FontManager::fontNameCache;

font_id FontManager::LoadFont(const std::string& path, int size) {
    font_id id;
    std::string textId = path + std::to_string(size);
    if (!fontNameCache.contains(textId)) {
        id = GetNextId();
        fontNameCache[textId] = id;
    } else {
        id = fontNameCache[textId];
    }

    if (!fontCache.contains(id)) {
        TTF_Font* font = TTF_OpenFont(path.c_str(), size);
        if (font == nullptr) {
            OLog::log(OLog::ERROR, SDL_GetError());
            throw std::runtime_error(SDL_GetError());
        }
        fontCache[id] = font;
    }

    return id;
}

TTF_Font* FontManager::GetFont(const font_id id) { return fontCache.at(id); }

void FontManager::ClearCache() {
    for (auto& entry : fontCache) {
        SDL_Deleter{}(entry.second);
    }
    fontCache.clear();
}

font_id FontManager::GetNextId() {
    static font_id next_id = 0;
    return next_id++;
}