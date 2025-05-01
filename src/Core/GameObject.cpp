/**
 * @file GameObject.cpp
 * @author Owen McManus
 * @date 2025/4/16
 */

#include "GameObject.h"
#include "../Components/Component.h"

namespace OEngine {
int GameObject::nextID = 0;

GameObject::GameObject() : id(nextID++) {}

void GameObject::Update(float deltaTime) {
    for (auto& [_, comp] : components) {
        comp->Update(deltaTime);
    }
}

int GameObject::GetID() const { return id; }

} // namespace OEngine