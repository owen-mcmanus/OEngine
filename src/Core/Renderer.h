/**
 * @file Renderer.h
 * @author Owen McManus
 * @date 2025/9/4
 */

#pragma once

#include "../AssetManager/TextureManager.h"
#include "../Components/PrimitiveSprite.h"
#include "../Events/EventManager.h"
#include "../GameObjects/Camera.h"
#include "../Utils/Color.h"
#include "../Utils/SDLDeleter.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <SDL3/SDL_render.h>
#include <iostream>
#include <memory>

namespace OEngine {
class Transform;

namespace AssetManager {
class TextureCache;
}

class Sprite;

class Renderer {
  public:
    explicit Renderer(SDL_Renderer* rawRenderer);
    ~Renderer();

    /**
     * @brief Clears the current rendering target.
     *
     * Clears the screen or render target, making it ready for new content to be drawn. This will
     * only occur if rendering is not paused.
     */
    void Clear() const;

    /**
     * @brief Presents the current rendering target to the screen.
     *
     * Updates the screen with the contents of the rendering target (i.e., the current frame). This
     * will only occur if rendering is not paused.
     */
    void Present() const;

    /**
     * @brief Pauses rendering.
     *
     * Pauses the rendering operations. All subsequent rendering operations (e.g., Clear, Present)
     * will not affect the screen until resumed.
     */
    void Pause();

    /**
     * @brief Resumes rendering after being paused.
     *
     * Resumes rendering operations after they have been paused.
     */
    void Resume();

    /**
     * @brief Sets the drawing color for subsequent rendering operations.
     *
     * Sets the color used for drawing operations like lines, points, and shapes. The color values
     * are expected to be in the range of 0 to 255.
     *
     * @param r The red component of the color (0-255).
     * @param g The green component of the color (0-255).
     * @param b The blue component of the color (0-255).
     * @param a The alpha (transparency) component of the color (0-255).
     */
    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

    /**
     * @brief Sets the background color and clears the screen.
     *
     * Sets the background color for the rendering target and then clears the screen with that
     * color. The original drawing color is restored after the background is set.
     *
     * @param r The red component of the background color (0-255).
     * @param g The green component of the background color (0-255).
     * @param b The blue component of the background color (0-255).
     * @param a The alpha (transparency) component of the background color (0-255).
     */
    void SetBackground(const Color& color) const;

    /**
     * @brief Draws a single point at the specified coordinates.
     *
     * Draws a point at the given (x, y) position. This will only happen if rendering is not paused.
     *
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     * @param color
     */
    void DrawPoint(float x, float y, const Color& color) const;

    /**
     * @brief Draws a line between two points.
     *
     * Draws a line from (x1, y1) to (x2, y2). This will only happen if rendering is not paused.
     *
     * @param x1 The x-coordinate of the starting point.
     * @param y1 The y-coordinate of the starting point.
     * @param x2 The x-coordinate of the ending point.
     * @param y2 The y-coordinate of the ending point.
     */
    void DrawLine(float x1, float y1, float x2, float y2, const Color& color) const;

    /**
     * @brief Draws a rectangle.
     *
     * Draws an unfilled rectangle at the given (x, y) position with the specified width and height.
     * This will only happen if rendering is not paused.
     *
     * @param x The x-coordinate of the top-left corner of the rectangle.
     * @param y The y-coordinate of the top-left corner of the rectangle.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     */
    void DrawRect(float x, float y, float w, float h, const Color& color) const;

    /**
     * @brief Draws a filled rectangle.
     *
     * Draws a filled rectangle at the given (x, y) position with the specified width and height.
     * This will only happen if rendering is not paused.
     *
     * @param x The x-coordinate of the top-left corner of the rectangle.
     * @param y The y-coordinate of the top-left corner of the rectangle.
     * @param w The width of the rectangle.
     * @param h The height of the rectangle.
     */
    void FillRect(float x, float y, float w, float h, const Color& color) const;

    /**
     * @brief Renders a sprite onto the screen.
     *
     * This method renders the sprite by fetching its texture from the texture cache
     * and drawing it at the destination rectangle provided by the sprite.
     *
     * @param sprite The sprite to be rendered. The sprite must have a valid surface ID and
     *               a destination rectangle defined for positioning.
     * @param transform
     */
    // void RenderSprite(const Sprite& sprite, const Transform& transform) const;

    /**
     * @brief Renders a sprite with rotation.
     *
     * This method renders the sprite with a rotation. The sprite's texture is fetched
     * from the texture cache and drawn at the destination rectangle provided by the sprite.
     * The sprite is rotated around its center point.
     *
     * @param sprite The sprite to be rendered. The sprite must have a valid surface ID,
     *               a destination rectangle, and a rotation angle defined.
     * @param transform
     *
     * @note The rotation is applied around the center of the sprite, and flipping is
     *       disabled (no mirroring).
     */
    void RenderSpriteWithRotation(const Sprite& sprite, const Transform& transform) const;

    void RenderPrimitiveSprite(const PrimitiveSprite& sprite, const Transform& transform) const;

    void RenderBackground(const Background& background) const;
    [[nodiscard]] SDL_Renderer& GetSDLRenderer() const;

  private:
    void SetColor(const Color& color) const;
    bool BoundingBoxOnScreen(SDL_FRect rect) const;
    bool BoundingCircleOnScreen(int x, int y, int r2) const;

    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<AssetManager::TextureCache> texture_cache;
    glm::mat3 viewMatrix = glm::mat3(1.0f);
    double viewRotation = 0.0f;
    double viewScale = 1.0f;
    EventListener<ChangeViewEvent> changeViewListener = [this](const ChangeViewEvent& e) {
        this->viewMatrix = e.viewMatrix;
        this->viewRotation = e.rotation * 180.0 / M_PI;
        this->viewScale = e.scale;
    };
    bool rendering_paused = false;
};

} // namespace OEngine