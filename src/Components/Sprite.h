/**
 * @file Sprite.h
 * @author Owen McManus
 * @date 2025/9/16
 */

#pragma once

#include "../Utils/SDLDeleter.h"
#include "Component.h"

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
    ~Sprite() = default;

    /**
     * @brief Updates the sprite's position and rotation using the center as the origin.
     *
     * @param x New x-coordinate of the center.
     * @param y New y-coordinate of the center.
     * @param rotation New rotation in degrees.
     */
    void UpdateOriginCenter(float x, float y, float rotation);

    /**
     * @brief Updates the sprite's position and rotation using the top-left corner as the origin.
     *
     * @param x New x-coordinate of the corner.
     * @param y New y-coordinate of the corner.
     * @param rotation New rotation in degrees.
     */
    void UpdateOriginCorner(float x, float y, float rotation);

    /// @return The sprite's x-position.
    [[nodiscard]] float GetX() const;
    /// @return The sprite's y-position.
    [[nodiscard]] float GetY() const;
    /// @return The sprite's current rotation in degrees.
    [[nodiscard]] float GetRotation() const;
    /// @return The width of the sprite.
    [[nodiscard]] int GetWidth() const;
    /// @return The height of the sprite.
    [[nodiscard]] int GetHeight() const;
    /// @return The surface ID associated with the sprite.
    [[nodiscard]] AssetManager::surface_id GetSurfaceId() const;
    /// @return A pointer to the destination rectangle used for rendering.
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
