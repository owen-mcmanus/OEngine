/**
 * @file Transform.h
 * @author Owen McManus
 * @date 2025/5/1
 */

#pragma once
#include "Component.h"

#include <glm/vec2.hpp>
#include <memory>
#include <vector>

namespace OEngine {
class Transform : public Component {
  public:
    Transform() = default;
    explicit Transform(
        const double x,
        const double y,
        const double rotation = 0,
        const double scale_x = 1,
        const double scale_y = 1)
        : localPosition(glm::vec2(x, y)), localRotation(rotation), localScale(scale_x, scale_y) {};
    explicit Transform(
        const glm::vec2 position,
        const double rotation = 0,
        const glm::vec2 scale = {1, 1})
        : localPosition(position), localRotation(rotation), localScale(scale) {};

    glm::vec2 localPosition{0.0f, 0.0f};
    double localRotation{0.0f};
    glm::vec2 localScale{1.0f, 1.0f};

    [[nodiscard]] glm::vec2 GetWorldPosition() const;
    [[nodiscard]] double GetWorldRotation() const;
    [[nodiscard]] glm::vec2 GetWorldScale() const;

    void Translate(const glm::vec2& amount);
    void SetParent(const std::weak_ptr<Transform>& newParent);
    void LockRotation(float value);
    void UnlockRotation();

  private:
    std::weak_ptr<Transform> parent;
    bool rotationLocked = false;
    float rotationLockedValue = 0;
};
} // namespace OEngine
