/**
 * @file Sprite.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "Sprite.h"

#include "../AssetManager/TextureManager.h"
#include "AssetManager/FontManager.h"
#include "Utils/Color.h"

#include <cmath>

using namespace OEngine;

Sprite::Sprite(const std::string& texturesheet, int width, int height)
    : width(width), height(height) {
    surf_id = AssetManager::TextureManager::LoadSurface(texturesheet);
}

Sprite::Sprite(
    const std::string& fontName,
    int fontSize,
    const std::string& text,
    const Color& color) {
    surf_id = AssetManager::TextureManager::CreateText(fontName, fontSize, text, color);
    SDL_Surface* s = AssetManager::TextureManager::GetSurface(surf_id);
    width = s->w;
    height = s->h;
}

int Sprite::GetWidth() const { return width; }

int Sprite::GetHeight() const { return height; }

AssetManager::surface_id Sprite::GetSurfaceId() const { return surf_id; }
