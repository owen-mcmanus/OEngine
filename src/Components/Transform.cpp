/**
 * @file Transform.cpp
 * @author Owen McManus
 * @date 2025/5/1
 */

#include "Transform.h"
#include "../Core/GameObject.h"

#include <iostream>

using namespace OEngine;

glm::vec2 Transform::GetWorldPosition() const {
    if (auto p = parent.lock()) {
        return p->GetWorldPosition() + localPosition;
    }
    return localPosition;
}

float Transform::GetWorldRotation() const {
    if (auto p = parent.lock()) {
        return p->GetWorldRotation() + localRotation;
    }
    return localRotation;
}

glm::vec2 Transform::GetWorldScale() const {
    if (auto p = parent.lock()) {
        return p->GetWorldScale() * localScale;
    }
    return localScale;
}

void Transform::Translate(const glm::vec2& amount) { localPosition += amount; }

void Transform::SetParent(const std::weak_ptr<Transform>& newParent) {
    auto self = owner->GetCacheableComponent<Transform>();

    if (auto currentParent = parent.lock()) {
        auto& siblings = currentParent->children;
        std::erase_if(siblings, [&](const std::weak_ptr<Transform>& wptr) {
            return !wptr.owner_before(self) && !self.owner_before(wptr);
        });
    }

    parent = newParent;
    if (auto currentParent = parent.lock()) {
        currentParent->children.push_back(self);
    }
}