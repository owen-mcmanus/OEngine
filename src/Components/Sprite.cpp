/**
 * @file Sprite.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "Sprite.h"

#include "../AssetManager/TextureManager.h"
#include "Utils/Color.h"

using namespace OEngine;

Sprite::Sprite(const std::filesystem::path& texturesheet, int width, int height)
    : width(width), height(height) {
    surf_id = AssetManager::TextureManager::LoadSurface(texturesheet);
}

Sprite::Sprite(
    const std::filesystem::path& fontName,
    int fontSize,
    const std::string& text,
    const Color& color,
    int wrapWidth) {
    surf_id = AssetManager::TextureManager::CreateText(fontName, fontSize, text, color, wrapWidth);
    SDL_Surface* s = AssetManager::TextureManager::GetSurface(surf_id);
    width = s->w;
    height = s->h;
}

int Sprite::GetWidth() const { return width; }

int Sprite::GetHeight() const { return height; }

AssetManager::surface_id Sprite::GetSurfaceId() const { return surf_id; }

void Sprite::SetWidth(int width) { this->width = width; }

void Sprite::SetHeight(int height) { this->height = height; }
