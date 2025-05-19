/**
 * @file TextureManager.cpp
 * @author Owen McManus
 * @date 2025/4/9
 */

#include "TextureManager.h"

#include "../Utils/SDLDeleter.h"
#include "FontManager.h"

#include <SDL3_image/SDL_image.h>
#include <olog.h>
#include <stdexcept>

using namespace OEngine::AssetManager;

std::unordered_map<surface_id, SDL_Surface*> TextureManager::surface_cache;
std::unordered_map<std::string, surface_id> TextureManager::name_cache;

surface_id TextureManager::LoadSurface(const std::string& path) {
    surface_id id;
    if (!name_cache.contains(path)) {
        id = GetNextId();
        name_cache[path] = id;
    } else {
        id = name_cache[path];
    }

    if (!surface_cache.contains(id)) {
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            OLog::log(OLog::ERROR, SDL_GetError());
            throw std::runtime_error(SDL_GetError());
        }
        surface_cache[id] = surface;
    }

    return id;
}

SDL_Surface* TextureManager::GetSurface(const surface_id id) { return surface_cache.at(id); }

void TextureManager::ClearCache() {
    for (auto& entry : surface_cache) {
        SDL_Deleter{}(entry.second);
    }
    surface_cache.clear();
}

surface_id TextureManager::CreateText(
    const std::string& fontName,
    int fontSize,
    const std::string& text,
    const Color& color) {
    int fontId = FontManager::LoadFont(fontName, fontSize);
    TTF_Font* font = FontManager::GetFont(fontId);
    SDL_Surface* surface =
        TTF_RenderText_Blended_Wrapped(font, text.c_str(), text.length(), color.toSDLColor(), 0);

    surface_id id = GetNextId();
    surface_cache[id] = surface;
    return id;
}

surface_id TextureManager::GetNextId() {
    static surface_id next_id = 0;
    return next_id++;
}