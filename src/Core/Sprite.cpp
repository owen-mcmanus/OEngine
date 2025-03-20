#include "Sprite.h"

#include "../AssetManager/TextureManager.h"

#include <SDL2/SDL_image.h>
#include <olog.h>

using namespace OEngine;

Sprite::Sprite(const std::string& texturesheet, int width, int height)
    : x(0), y(0), rotation(0), width(width), height(height), destRect(0, 0, width, height) {
    surf_id = AssetManager::TextureManager::LoadSurface(texturesheet);
}

void Sprite::UpdateOriginCenter(double x, double y, double rotation) {
    this->x = x;
    this->y = y;
    this->rotation = std::fmod(rotation, 360);

    destRect.x = static_cast<int>(x) - (width / 2);
    destRect.y = static_cast<int>(y) - (height / 2);
}

void Sprite::UpdateOriginCorner(double x, double y, double rotation) {
    this->x = x;
    this->y = y;
    this->rotation = std::fmod(rotation, 360);

    destRect.x = static_cast<int>(x);
    destRect.y = static_cast<int>(y);
}

// void Sprite::SetOpacity(int opacity) { SDL_SetSurfaceAlphaMod(surface.get(), opacity); }

double Sprite::GetX() const { return x; }

double Sprite::GetY() const { return y; }

double Sprite::GetRotation() const { return rotation; }

int Sprite::GetWidth() const { return width; }

int Sprite::GetHeight() const { return height; }

int Sprite::GetSurfaceId() const { return surf_id; }

const SDL_Rect* Sprite::GetDestRect() const { return &destRect; }
