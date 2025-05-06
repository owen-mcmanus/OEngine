/**
 * @file Renderer.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "Renderer.h"

#include "../Components/PrimitiveSprite.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"

#include "../Events/EventManager.h"

#include <iostream>
#include <olog.h>

using namespace OEngine;

Renderer::Renderer(SDL_Renderer* rawRenderer) {
    SDL_SetRenderVSync(rawRenderer, 1);
    SDL_SetRenderDrawBlendMode(rawRenderer, SDL_BLENDMODE_BLEND);

    renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(rawRenderer);
    texture_cache = std::make_unique<AssetManager::TextureCache>(*renderer);

    EventManager::AddListener<ChangeViewEvent>(&changeViewListener);
}

Renderer::~Renderer() { EventManager::RemoveListener<ChangeViewEvent>(&changeViewListener); }

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

void Renderer::SetBackground(const Color& color) const {
    SetColor(color);
    Clear();
}

void Renderer::DrawPoint(float x, float y, const Color& color) const {
    if (!rendering_paused) {
        SDL_RenderPoint(renderer.get(), x, y);
    }
}

void Renderer::DrawLine(float x1, float y1, float x2, float y2, const Color& color) const {
    if (!rendering_paused) {
        SetColor(color);
        SDL_RenderLine(renderer.get(), x1, y1, x2, y2);
    }
}

void Renderer::DrawRect(float x, float y, float w, float h, const Color& color) const {
    if (!rendering_paused) {
        SetColor(color);
        SDL_FRect rect = {x, y, w, h};
        SDL_RenderRect(renderer.get(), &rect);
    }
}

void Renderer::FillRect(float x, float y, float w, float h, const Color& color) const {
    if (!rendering_paused) {
        SetColor(color);
        SDL_FRect rect = {x, y, w, h};
        SDL_RenderFillRect(renderer.get(), &rect);
    }
}

// void Renderer::RenderSprite(const Sprite& sprite, const Transform& transform) const {
//     SDL_FRect destRec{};
//
//     glm::vec3 worldPos(transform.GetWorldPosition(), 1.0);
//     glm::vec3 screenPos = viewMatrix * worldPos;
//     destRec.x = screenPos.x;
//     destRec.y = screenPos.y;
//     destRec.w = static_cast<float>(sprite.GetWidth());
//     destRec.h = static_cast<float>(sprite.GetHeight());
//
//     SDL_RenderTexture(
//         renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr, &destRec);
// }

void Renderer::RenderSpriteWithRotation(const Sprite& sprite, const Transform& transform) const {
    SDL_FPoint pt;
    pt.x = sprite.GetWidth() / 2;
    pt.y = sprite.GetHeight() / 2;

    SDL_FRect destRec{};
    glm::vec3 worldPos(transform.GetWorldPosition(), 1.0);
    glm::vec3 screenPos = viewMatrix * worldPos;
    destRec.x = screenPos.x;
    destRec.y = screenPos.y;
    destRec.w = static_cast<float>(sprite.GetWidth());
    destRec.h = static_cast<float>(sprite.GetHeight());

    SDL_RenderTextureRotated(
        renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr, &destRec,
        transform.GetWorldRotation() - viewRotation, &pt, SDL_FLIP_NONE);
}

void Renderer::RenderPrimitiveSprite(const PrimitiveSprite& sprite, const Transform& transform)
    const {
    glm::vec3 worldPosition{transform.GetWorldPosition(), 1.0};
    glm::vec3 screenPosition;
    glm::vec2 screenScale = {sprite.width, sprite.height};
    if (true) {
        screenPosition = viewMatrix * worldPosition;
        screenScale = static_cast<float>(viewScale) * screenScale;
    } else {
        screenPosition = worldPosition;
    }
    switch (sprite.type) {
    case PrimitiveSpriteType::POINT: {
        DrawPoint(screenPosition.x, screenPosition.y, sprite.color);
        break;
    }
    case PrimitiveSpriteType::LINE: {
        glm::vec3 endPosition = {sprite.width, sprite.height, 1.0f};
        endPosition = viewMatrix * endPosition;
        DrawLine(screenPosition.x, screenPosition.y, endPosition.x, endPosition.y, sprite.color);
        break;
    }
    case PrimitiveSpriteType::RECTANGLE: {
        DrawRect(screenPosition.x, screenPosition.y, screenScale.x, screenScale.y, sprite.color);
        break;
    }
    case PrimitiveSpriteType::FILL_RECTANGLE: {
        FillRect(screenPosition.x, screenPosition.y, screenScale.x, screenScale.y, sprite.color);
        break;
    }
    default: {
        break;
    }
    }
}

void Renderer::RenderBackground(const Background& background) const {
    SetBackground(background.color);
}

SDL_Renderer& Renderer::GetSDLRenderer() const { return *renderer; }

void Renderer::SetColor(const Color& color) const {
    SDL_SetRenderDrawColor(
        renderer.get(), color.r * 255, color.g * 255, color.b * 255, color.a * 255);
}