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
    SDL_SetRenderVSync(rawRenderer, -1);
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
        if (!BoundingBoxOnScreen({x, y, 1, 1}))
            return;
        SDL_RenderPoint(renderer.get(), x, y);
    }
}

void Renderer::DrawLine(float x1, float y1, float width, float height, const Color& color) const {
    float x2 = x1 + width;
    float y2 = y1 + height;
    if (!rendering_paused) {
        if (!BoundingBoxOnScreen(
                {std::min(x1, x2), std::min(y1, y2), std::abs(x1 - x2), std::abs(y1 - y2)}))
            return;

        SetColor(color);
        SDL_RenderLine(renderer.get(), x1, y1, x2, y2);
    }
}

void Renderer::DrawRect(float x, float y, float w, float h, const Color& color) const {
    if (!rendering_paused) {
        if (!BoundingBoxOnScreen({x, y, w, h}))
            return;
        SetColor(color);
        SDL_FRect rect = {x, y, w, h};
        SDL_RenderRect(renderer.get(), &rect);
    }
}

void Renderer::FillRect(float x, float y, float w, float h, const Color& color) const {
    if (!rendering_paused) {
        if (!BoundingBoxOnScreen({x, y, w, h}))
            return;
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

void Renderer::RenderSpriteWithRotation(
    const Sprite& sprite,
    const Transform& transform,
    bool inWorld) const {
    SDL_FPoint pt;
    pt.x = sprite.GetWidth() / 2;
    pt.y = sprite.GetHeight() / 2;

    SDL_FRect destRec{};
    glm::vec3 worldPos(transform.GetWorldPosition(), 1.0);

    if (inWorld) {
        glm::vec3 screenPos = viewMatrix * worldPos;
        destRec.x = screenPos.x;
        destRec.y = screenPos.y;
        if (sprite.GetScaleOnZoom()) {
            destRec.w = static_cast<float>(sprite.GetWidth()) * static_cast<float>(viewScale);
            destRec.h = static_cast<float>(sprite.GetHeight()) * static_cast<float>(viewScale);
            pt.x = pt.x * static_cast<float>(viewScale);
            pt.y = pt.y * static_cast<float>(viewScale);
        } else {
            destRec.w = static_cast<float>(sprite.GetWidth());
            destRec.h = static_cast<float>(sprite.GetHeight());
        }
    } else {
        destRec.x = worldPos.x;
        destRec.y = worldPos.y;
        destRec.w = static_cast<float>(sprite.GetWidth());
        destRec.h = static_cast<float>(sprite.GetHeight());
    }

    SDL_FRect bounding;
    int rot = transform.GetWorldRotation() - viewRotation;
    if (rot == 0 || rot == 180) {
        bounding = {destRec.x, destRec.y, destRec.w, destRec.h};
    } else if (rot == 90 || rot == 270) {
        bounding = {destRec.x, destRec.y, destRec.h, destRec.w};
    } else {
        int r2 = (destRec.w * destRec.w + destRec.h * destRec.h) * 0.25f;
        if (!BoundingCircleOnScreen(destRec.x + destRec.w / 2, destRec.y + destRec.h / 2, r2))
            return;

        float rotf = transform.GetWorldRotation() - viewRotation * 3.14159f / 180.0f;
        float cx = destRec.x + destRec.w / 2;
        float cy = destRec.y + destRec.h / 2;
        float dx = abs(destRec.w * std::cos(rotf)) / 2 + abs(destRec.h * std::sin(rotf)) / 2;
        float dy = abs(destRec.w * std::sin(rotf)) / 2 + abs(destRec.h * std::cos(rotf)) / 2;
        bounding = {cx - dx, cy - dy, dx * 2, dy * 2};
    }

    if (!BoundingBoxOnScreen(bounding))
        return;

    SDL_RenderTextureRotated(
        renderer.get(), texture_cache->GetTexture(sprite.GetSurfaceId()), nullptr, &destRec,
        transform.GetWorldRotation() - viewRotation, &pt, SDL_FLIP_NONE);
}

void Renderer::RenderPrimitiveSprite(
    const PrimitiveSprite& sprite,
    const Transform& transform,
    bool inWorld) const {
    glm::vec3 worldPosition{transform.GetWorldPosition(), 1.0};
    glm::vec3 screenPosition;
    glm::vec2 screenScale = {sprite.width, sprite.height};
    if (inWorld) {
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
        // glm::vec3 endPosition = {sprite.width, sprite.height, 1.0f};
        // endPosition = viewMatrix * endPosition;
        DrawLine(screenPosition.x, screenPosition.y, screenScale.x, screenScale.y, sprite.color);
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

bool Renderer::BoundingBoxOnScreen(const SDL_FRect rect) const {
    // SetColor(Color::Red);
    // SDL_RenderRect(renderer.get(), &rect);
    if (rect.x > 1920 || rect.y > 1080) {
        return false;
    }
    if (rect.x + rect.w < 0 || rect.y + rect.h < 0) {
        return false;
    }
    return true;
}

bool Renderer::BoundingCircleOnScreen(int x, int y, int r2) const {
    const int clampedX = std::min(std::max(x, 0), 1920 - 1);
    const int clampedY = std::min(std::max(y, 0), 1080 - 1);

    const int dx = x - clampedX;
    const int dy = y - clampedY;

    return int64_t(dx) * dx + int64_t(dy) * dy <= int64_t(r2);
}