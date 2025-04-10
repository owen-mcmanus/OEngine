/**
 * @file Sprite.h
 * @author Owen McManus
 * @date 2025/9/4
 */

#pragma once

#include "../Utils/SDLDeleter.h"

#include <memory>
#include <string>

namespace OEngine {

namespace AssetManager {
using surface_id = int;
}

class Sprite {
  public:
    Sprite(const std::string& texturesheet, int width, int height);
    ~Sprite() = default;

    void UpdateOriginCenter(float x, float y, float rotation);
    void UpdateOriginCorner(float x, float y, float rotation);

    [[nodiscard]] float GetX() const;
    [[nodiscard]] float GetY() const;
    [[nodiscard]] float GetRotation() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] AssetManager::surface_id GetSurfaceId() const;
    [[nodiscard]] const SDL_FRect* GetDestRect() const;

  private:
    float x;
    float y;
    float rotation;

    int width;
    int height;

    SDL_FRect destRect;
    AssetManager::surface_id surf_id;
};

} // namespace OEngine
