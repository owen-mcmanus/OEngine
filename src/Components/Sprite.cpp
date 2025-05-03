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
    : width(width), height(height) {
    surf_id = AssetManager::TextureManager::LoadSurface(texturesheet);
}

int Sprite::GetWidth() const { return width; }

int Sprite::GetHeight() const { return height; }

AssetManager::surface_id Sprite::GetSurfaceId() const { return surf_id; }
