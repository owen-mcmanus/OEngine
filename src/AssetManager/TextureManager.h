/**
 * @file TextureManager.h
 * @author Owen McManus
 * @date 2025/4/9
 */

#pragma once

#include "Utils/Color.h"

#include <SDL3/SDL.h>
#include <filesystem>
#include <string>
#include <unordered_map>

namespace OEngine::AssetManager {

using surface_id = int;

class TextureManager {
  public:
    TextureManager() = delete;
    static surface_id LoadSurface(const std::filesystem::path& path);
    static SDL_Surface* GetSurface(surface_id id);
    static void ClearCache();

    static surface_id CreateText(
        const std::filesystem::path& fontName,
        int fontSize,
        const std::string& text,
        const Color& color,
        int wrapWidth = 0);

  private:
    static surface_id GetNextId();

    static std::unordered_map<surface_id, SDL_Surface*> surface_cache;
    static std::unordered_map<std::string, surface_id> name_cache;
};

class TextureCache {
  public:
    explicit TextureCache(SDL_Renderer& renderer);
    ~TextureCache();

    SDL_Texture* GetTexture(surface_id id);

  private:
    SDL_Renderer& renderer;
    std::unordered_map<surface_id, SDL_Texture*> texture_cache;
};

} // namespace OEngine::AssetManager
