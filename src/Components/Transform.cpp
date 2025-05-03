/**
 * @file Transform.cpp
 * @author Owen McManus
 * @date 2025/5/1
 */

#include "Transform.h"
#include "../Core/GameObject.h"

using namespace OEngine;

glm::vec2 Transform::GetWorldPosition() const {
    if (auto p = parent.lock()) {
        return p->GetWorldPosition() + localPosition;
    }
    return localPosition;
}

double Transform::GetWorldRotation() const {
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
    // if (auto currentParent = parent.lock()) {
    //     auto& siblings = currentParent->children;
    //     std::erase(siblings, this);
    // }

    parent = newParent;
    // if (auto currentParent = parent.lock()) {
    //     currentParent->children.push_back(this);
    // }
}