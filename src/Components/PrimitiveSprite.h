/**
 * @file PrimitiveSprite.h
 * @author Owen McManus
 * @date 2025/5/4
 */

#pragma once
#include "../Utils/Color.h"
#include "Component.h"

namespace OEngine {

enum class PrimitiveSpriteType { POINT, LINE, RECTANGLE, FILL_RECTANGLE };

class Background : public Component {
  public:
    explicit Background(const Color& color) : color(color) {};
    Color color;
};

class PrimitiveSprite : public Component {
  public:
    explicit PrimitiveSprite(
        const PrimitiveSpriteType type,
        const Color& color,
        float width = 0,
        float height = 0)
        : type(type), color(color), width(width), height(height) {};
    PrimitiveSpriteType type;
    Color color;
    double width;
    double height;
};
}; // namespace OEngine