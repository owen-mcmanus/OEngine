#include "Renderer.h"

#include <olog.h>

using namespace OEngine;

Renderer::Renderer(SDL_Window* window) : rendering_paused(false) {
    SDL_Renderer* rawRenderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rawRenderer) {
        OLog::log(OLog::CRITICAL, SDL_GetError());
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }
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

void Renderer::DrawPoint(int x, int y) const {
    if (!rendering_paused) {
        SDL_RenderDrawPoint(renderer.get(), x, y);
    }
}

void Renderer::DrawLine(int x1, int y1, int x2, int y2) const {
    if (!rendering_paused) {
        SDL_RenderDrawLine(renderer.get(), x1, y1, x2, y2);
    }
}

void Renderer::DrawRect(int x, int y, int w, int h) const {
    if (!rendering_paused) {
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderDrawRect(renderer.get(), &rect);
    }
}

void Renderer::FillRect(int x, int y, int w, int h) const {
    if (!rendering_paused) {
        SDL_Rect rect = {x, y, w, h};
        SDL_RenderFillRect(renderer.get(), &rect);
    }
}

void Renderer::RenderSprite(Sprite& sprite) {
    SDL_RenderCopy(
        renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr,
        sprite.GetDestRect());
}

void Renderer::RenderSpriteWithRotation(Sprite& sprite) {
    SDL_Point pt;
    pt.x = sprite.GetWidth() / 2;
    pt.y = sprite.GetHeight() / 2;

    SDL_RenderCopyEx(
        renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr,
        sprite.GetDestRect(), sprite.GetRotation(), &pt, SDL_FLIP_NONE);
}

SDL_Renderer& Renderer::GetSDLRenderer() const { return *renderer; }