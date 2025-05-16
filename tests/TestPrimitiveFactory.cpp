// PrimitiveFactoryTests.cpp
// Unit tests for OEngine::PrimitiveFactory using Google Test

#include <gtest/gtest.h>

#include "../src/Components/PrimitiveSprite.h"
#include "../src/Components/Transform.h"
#include "../src/GameObjects/PrimitiveFactory.h"

using namespace OEngine;

namespace {

// Helper color constant (adjust constructor/signature to your Color implementation)
static const Color kRed(255, 0, 0, 255);

TEST(PrimitiveFactoryTest, CreateRectangle) {
    const double kX = 10.0, kY = 20.0, kWidth = 30.0, kHeight = 40.0;
    const int kLayer = 7;

    auto obj = PrimitiveFactory::CreateRectangle(kX, kY, kWidth, kHeight, kRed, kLayer);

    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->layer, kLayer);

    // Validate Transform component
    auto transform = obj->GetComponent<Transform>();
    ASSERT_NE(transform, nullptr);
    EXPECT_DOUBLE_EQ(transform->GetWorldPosition().x, kX);
    EXPECT_DOUBLE_EQ(transform->GetWorldPosition().y, kY);

    // Validate PrimitiveSprite component
    auto sprite = obj->GetComponent<PrimitiveSprite>();
    ASSERT_NE(sprite, nullptr);
    EXPECT_EQ(sprite->type, PrimitiveSpriteType::RECTANGLE);
    EXPECT_EQ(sprite->color, kRed);
    EXPECT_DOUBLE_EQ(sprite->width, kWidth);
    EXPECT_DOUBLE_EQ(sprite->height, kHeight);
}

TEST(PrimitiveFactoryTest, CreateFilledRectangle) {
    const double kX = 5.0, kY = 5.0, kWidth = 100.0, kHeight = 50.0;
    const int kLayer = 1;

    auto obj = PrimitiveFactory::CreateFilledRectangle(kX, kY, kWidth, kHeight, kRed, kLayer);

    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->layer, kLayer);

    auto sprite = obj->GetComponent<PrimitiveSprite>();
    ASSERT_NE(sprite, nullptr);
    EXPECT_EQ(sprite->type, PrimitiveSpriteType::FILL_RECTANGLE);
    EXPECT_EQ(sprite->color, kRed);
}

TEST(PrimitiveFactoryTest, CreateLine) {
    const double kX1 = 1.0, kY1 = 2.0, kX2 = 3.0, kY2 = 4.0;
    const int kLayer = 2;

    auto obj = PrimitiveFactory::CreateLine(kX1, kY1, kX2, kY2, kRed, kLayer);

    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->layer, kLayer);

    auto transform = obj->GetComponent<Transform>();
    ASSERT_NE(transform, nullptr);
    EXPECT_DOUBLE_EQ(transform->GetWorldPosition().x, kX1);
    EXPECT_DOUBLE_EQ(transform->GetWorldPosition().y, kY1);

    auto sprite = obj->GetComponent<PrimitiveSprite>();
    ASSERT_NE(sprite, nullptr);
    EXPECT_EQ(sprite->type, PrimitiveSpriteType::LINE);
    // NOTE: PrimitiveSprite uses width/height to store x2/y2 for lines in current implementation
    EXPECT_DOUBLE_EQ(sprite->width, kX2);
    EXPECT_DOUBLE_EQ(sprite->height, kY2);
}

TEST(PrimitiveFactoryTest, CreatePoint) {
    const double kX = 0.0, kY = 0.0;
    const int kLayer = 0;

    auto obj = PrimitiveFactory::CreatePoint(kX, kY, kRed, kLayer);

    ASSERT_NE(obj, nullptr);
    EXPECT_EQ(obj->layer, kLayer);

    auto transform = obj->GetComponent<Transform>();
    ASSERT_NE(transform, nullptr);
    EXPECT_DOUBLE_EQ(transform->GetWorldPosition().x, kX);
    EXPECT_DOUBLE_EQ(transform->GetWorldPosition().y, kY);

    auto sprite = obj->GetComponent<PrimitiveSprite>();
    ASSERT_NE(sprite, nullptr);
    EXPECT_EQ(sprite->type, PrimitiveSpriteType::POINT);
    EXPECT_DOUBLE_EQ(sprite->width, 1.0);
    EXPECT_DOUBLE_EQ(sprite->height, 1.0);
}

} // namespace
