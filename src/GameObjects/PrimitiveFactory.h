/**
 * @file PrimitiveFactory.h
 * @author Owen McManus
 * @date 2025/5/16
 */

#pragma once
#include "../Core/GameObject.h"
#include <memory>

namespace OEngine {
class Color;

class PrimitiveFactory {
  public:
    static std::shared_ptr<GameObject>
    CreateRectangle(double x, double y, double width, double height, Color color, int layer);

    static std::shared_ptr<GameObject>
    CreateFilledRectangle(double x, double y, double width, double height, Color color, int layer);

    static std::shared_ptr<GameObject>
    CreateLine(double x1, double y1, double width, double height, Color color, int layer);

    static std::shared_ptr<GameObject> CreatePoint(double x, double y, Color color, int layer);

    static std::shared_ptr<GameObject> CreateBackground(Color color);
};
} // namespace OEngine
