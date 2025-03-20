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

    void UpdateOriginCenter(double x, double y, double rotation);
    void UpdateOriginCorner(double x, double y, double rotation);
    // void SetOpacity(int opacity);

    [[nodiscard]] double GetX() const;
    [[nodiscard]] double GetY() const;
    [[nodiscard]] double GetRotation() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetSurfaceId() const;
    [[nodiscard]] const SDL_Rect* GetDestRect() const;

  private:
    double x;
    double y;
    double rotation;

    int width;
    int height;

    SDL_Rect destRect;
    AssetManager::surface_id surf_id;
};

} // namespace OEngine
