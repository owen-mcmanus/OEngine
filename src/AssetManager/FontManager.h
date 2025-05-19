/**
 * @file FontManager.h
 * @author Owen McManus
 * @date 2025/5/18
 */
#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <unordered_map>

namespace OEngine::AssetManager {

using font_id = int;

class FontManager {
  public:
    FontManager() = delete;
    static font_id LoadFont(const std::string& path, int size);
    static TTF_Font* GetFont(font_id id);
    static void ClearCache();

  private:
    static font_id GetNextId();

    static std::unordered_map<font_id, TTF_Font*> fontCache;
    static std::unordered_map<std::string, font_id> fontNameCache;
};
} // namespace OEngine::AssetManager
