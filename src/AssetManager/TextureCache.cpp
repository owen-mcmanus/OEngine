/**
 * @file TextureCache.cpp
 * @author Owen McManus
 * @date 2025/4/9
 */

#include "../Utils/SDLDeleter.h"
#include "TextureManager.h"

#include <olog.h>
#include <stdexcept>

using namespace OEngine::AssetManager;

TextureCache::TextureCache(SDL_Renderer& renderer) : renderer(renderer) {}

TextureCache::~TextureCache() {
    for (auto& entry : texture_cache) {
        SDL_Deleter{}(entry.second);
    }
}

SDL_Texture* TextureCache::GetTexture(surface_id id) {
    SDL_Texture* texture;
    if (!texture_cache.contains(id)) {
        texture = SDL_CreateTextureFromSurface(&renderer, TextureManager::GetSurface(id));
        if (texture == nullptr) {
            OLog::log(OLog::ERROR, SDL_GetError());
            throw std::runtime_error(SDL_GetError());
        }
        texture_cache[id] = texture;
    } else {
        texture = texture_cache[id];
    }

    return texture;
}
