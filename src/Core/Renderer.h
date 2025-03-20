#pragma once
#include "../AssetManager/TextureManager.h"
#include "SDLDeleter.h"
#include "Sprite.h"

#include <SDL_render.h>
#include <memory>
#include <unordered_map>

class Renderer {
  public:
    Renderer(SDL_Window* window);
    ~Renderer() = default;

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
    void SetBackground(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const;

    /**
     * @brief Draws a single point at the specified coordinates.
     *
     * Draws a point at the given (x, y) position. This will only happen if rendering is not paused.
     *
     * @param x The x-coordinate of the point.
     * @param y The y-coordinate of the point.
     */
    void DrawPoint(int x, int y) const;

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
    void DrawLine(int x1, int y1, int x2, int y2) const;

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
    void DrawRect(int x, int y, int w, int h) const;

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
    void FillRect(int x, int y, int w, int h) const;

    void RenderSprite(Sprite& sprite);
    void RenderSpriteWithRotation(Sprite& sprite);

    SDL_Renderer& GetSDLRenderer() const;

  private:
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<AssetManager::TextureCache> texture_cache;
    bool rendering_paused;
};
