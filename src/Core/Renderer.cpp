/**
 * @file Renderer.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "Renderer.h"

#include "Sprite.h"

#include <olog.h>
#include <stdexcept>

using namespace OEngine;

Renderer::Renderer(SDL_Renderer* rawRenderer) {
    renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(rawRenderer);

    texture_cache = std::make_unique<AssetManager::TextureCache>(*renderer);
}

void Renderer::Clear() const {
    if (!rendering_paused)
        SDL_RenderClear(renderer.get());
}

void Renderer::Present() const {
    if (!rendering_paused)
        SDL_RenderPresent(renderer.get());
}

void Renderer::Pause() { rendering_paused = true; }

void Renderer::Resume() { rendering_paused = false; }

void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
}

void Renderer::SetBackground(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
    Uint8 old_r, old_g, old_b, old_a;
    SDL_GetRenderDrawColor(renderer.get(), &old_r, &old_g, &old_b, &old_a);

    SetDrawColor(r, g, b, a);
    Clear();

    SetDrawColor(old_r, old_g, old_b, old_a);
}

void Renderer::DrawPoint(float x, float y) const {
    if (!rendering_paused) {
        SDL_RenderPoint(renderer.get(), x, y);
    }
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2) const {
    if (!rendering_paused) {
        SDL_RenderLine(renderer.get(), x1, y1, x2, y2);
    }
}

void Renderer::DrawRect(float x, float y, float w, float h) const {
    if (!rendering_paused) {
        SDL_FRect rect = {x, y, w, h};
        SDL_RenderRect(renderer.get(), &rect);
    }
}

void Renderer::FillRect(float x, float y, float w, float h) const {
    if (!rendering_paused) {
        SDL_FRect rect = {x, y, w, h};
        SDL_RenderFillRect(renderer.get(), &rect);
    }
}

void Renderer::RenderSprite(Sprite& sprite) const {
    SDL_RenderTexture(
        renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr,
        sprite.GetDestRect());
}

void Renderer::RenderSpriteWithRotation(Sprite& sprite) const {
    SDL_FPoint pt;
    pt.x = sprite.GetWidth() / 2;
    pt.y = sprite.GetHeight() / 2;

    SDL_RenderTextureRotated(
        renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr,
        sprite.GetDestRect(), sprite.GetRotation(), &pt, SDL_FLIP_NONE);
}

SDL_Renderer& Renderer::GetSDLRenderer() const { return *renderer; }