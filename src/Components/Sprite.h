/**
 * @file Sprite.h
 * @author Owen McManus
 * @date 2025/9/16
 */

#pragma once

#include "../Utils/SDLDeleter.h"
#include "Component.h"
#include "Utils/Color.h"

#include <memory>
#include <string>

namespace OEngine {

namespace AssetManager {
using surface_id = int;
}

/**
 * @brief Represents a textured image to be rendered on screen.
 *
 * A Sprite handles positional and rotational transformations,
 * and stores metadata like width, height, and associated surface ID.
 */
class Sprite : public Component {
  public:
    /**
     * @brief Constructs a sprite from a texture sheet.
     *
     * @param texturesheet The file path of the texture sheet.
     * @param width Width of the sprite in pixels.
     * @param height Height of the sprite in pixels.
     */
    Sprite(const std::string& texturesheet, int width, int height);
    Sprite(const std::string& fontName, int fontSize, const std::string& text, const Color& color);
    ~Sprite() override = default;

    /// @return The width of the sprite.
    [[nodiscard]] int GetWidth() const;
    /// @return The height of the sprite.
    [[nodiscard]] int GetHeight() const;
    /// @return The surface ID associated with the sprite.
    [[nodiscard]] AssetManager::surface_id GetSurfaceId() const;

  private:
    int width;
    int height;

    AssetManager::surface_id surf_id;
};

} // namespace OEngine
