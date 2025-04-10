/**
 * @file Sprite.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "Sprite.h"

#include "../AssetManager/TextureManager.h"

#include <cmath>

using namespace OEngine;

Sprite::Sprite(const std::string& texturesheet, int width, int height)
    : x(0), y(0), rotation(0), width(width), height(height),
      destRect(0, 0, static_cast<float>(width), static_cast<float>(height)) {
    surf_id = AssetManager::TextureManager::LoadSurface(texturesheet);
}

void Sprite::UpdateOriginCenter(float x, float y, float rotation) {
    this->x = x;
    this->y = y;
    this->rotation = fmodf(rotation, 360);

    destRect.x = x - (static_cast<float>(width) / 2);
    destRect.y = y - (static_cast<float>(height) / 2);
}

void Sprite::UpdateOriginCorner(float x, float y, float rotation) {
    this->x = x;
    this->y = y;
    this->rotation = fmodf(rotation, 360);

    destRect.x = x;
    destRect.y = y;
}

float Sprite::GetX() const { return x; }

float Sprite::GetY() const { return y; }

float Sprite::GetRotation() const { return rotation; }

int Sprite::GetWidth() const { return width; }

int Sprite::GetHeight() const { return height; }

AssetManager::surface_id Sprite::GetSurfaceId() const { return surf_id; }

const SDL_FRect* Sprite::GetDestRect() const { return &destRect; }
