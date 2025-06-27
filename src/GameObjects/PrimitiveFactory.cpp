/**
 * @file PrimitiveFactory.cpp
 * @author Owen McManus
 * @date 2025/5/16
 */

#include "PrimitiveFactory.h"
#include "../Components/PrimitiveSprite.h"
#include "../Components/Transform.h"

using namespace OEngine;

std::shared_ptr<GameObject> PrimitiveFactory::CreateRectangle(
    double x,
    double y,
    double width,
    double height,
    Color color,
    int layer) {
    auto box = std::make_shared<GameObject>(layer);
    box->AddComponent<Transform>(x, y);
    box->AddComponent<PrimitiveSprite>(PrimitiveSpriteType::RECTANGLE, color, width, height);
    return box;
}

std::shared_ptr<GameObject> PrimitiveFactory::CreateFilledRectangle(
    double x,
    double y,
    double width,
    double height,
    Color color,
    int layer) {
    auto box = std::make_shared<GameObject>(layer);
    box->AddComponent<Transform>(x, y);
    box->AddComponent<PrimitiveSprite>(PrimitiveSpriteType::FILL_RECTANGLE, color, width, height);
    return box;
}

std::shared_ptr<GameObject> PrimitiveFactory::CreateLine(
    double x1,
    double y1,
    double width,
    double height,
    Color color,
    int layer) {
    auto box = std::make_shared<GameObject>(layer);
    box->AddComponent<Transform>(x1, y1);
    box->AddComponent<PrimitiveSprite>(PrimitiveSpriteType::LINE, color, width, height);
    return box;
}

std::shared_ptr<GameObject>
PrimitiveFactory::CreatePoint(double x, double y, Color color, int layer) {
    auto box = std::make_shared<GameObject>(layer);
    box->AddComponent<Transform>(x, y);
    box->AddComponent<PrimitiveSprite>(PrimitiveSpriteType::POINT, color, 1, 1);
    return box;
}

std::shared_ptr<GameObject> PrimitiveFactory::CreateBackground(Color color) {
    auto background = std::make_shared<GameObject>(0);
    background->AddComponent<Background>(color);
    return background;
}