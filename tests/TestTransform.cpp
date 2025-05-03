#include "../src/Components/Transform.h"
#include <gtest/gtest.h>

using namespace OEngine;

class TransformTest : public ::testing::Test {
  protected:
    std::shared_ptr<Transform> parent;
    std::shared_ptr<Transform> child;

    void SetUp() override {
        parent = std::make_shared<Transform>(glm::vec2(10.0f, 20.0f), 30.0f, glm::vec2(2.0f, 2.0f));
        child = std::make_shared<Transform>(glm::vec2(5.0f, 5.0f), 15.0f, glm::vec2(0.5f, 0.5f));
        // Normally, owner is used for hierarchy but mocked out here
        // So we assign the parent manually
        child->SetParent(parent);
    }
};

TEST_F(TransformTest, DefaultConstructorInitializesCorrectly) {
    Transform t;
    EXPECT_EQ(t.localPosition, glm::vec2(0.0f, 0.0f));
    EXPECT_FLOAT_EQ(t.localRotation, 0.0f);
    EXPECT_EQ(t.localScale, glm::vec2(1.0f, 1.0f));
}

TEST_F(TransformTest, ParameterizedConstructorSetsValues) {
    Transform t(1.0f, 2.0f, 45.0f, 1.5f, 2.0f);
    EXPECT_EQ(t.localPosition, glm::vec2(1.0f, 2.0f));
    EXPECT_FLOAT_EQ(t.localRotation, 45.0f);
    EXPECT_EQ(t.localScale, glm::vec2(1.5f, 2.0f));
}

TEST_F(TransformTest, GetWorldPositionWithoutParent) {
    Transform t(glm::vec2(3.0f, 4.0f));
    EXPECT_EQ(t.GetWorldPosition(), glm::vec2(3.0f, 4.0f));
}

TEST_F(TransformTest, GetWorldPositionWithParent) {
    EXPECT_EQ(child->GetWorldPosition(), glm::vec2(15.0f, 25.0f));
}

TEST_F(TransformTest, GetWorldRotationWithParent) {
    EXPECT_FLOAT_EQ(child->GetWorldRotation(), 45.0f);
}

TEST_F(TransformTest, GetWorldScaleWithParent) {
    EXPECT_EQ(child->GetWorldScale(), glm::vec2(1.0f, 1.0f));
}

TEST_F(TransformTest, TranslateUpdatesLocalPosition) {
    Transform t;
    t.Translate(glm::vec2(3.0f, 4.0f));
    EXPECT_EQ(t.localPosition, glm::vec2(3.0f, 4.0f));
}

TEST_F(TransformTest, SetParentChangesHierarchy) {
    auto newParent = std::make_shared<Transform>(glm::vec2(100.0f, 0.0f));
    child->SetParent(newParent);
    EXPECT_EQ(child->GetWorldPosition(), glm::vec2(105.0f, 5.0f));
}
