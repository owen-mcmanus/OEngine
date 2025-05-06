/**
 * @file GameObject.cpp
 * @author Owen McManus
 * @date 2025/4/16
 */

#include "GameObject.h"
#include "../Components/Component.h"

namespace OEngine {
int GameObject::nextID = 0;

GameObject::GameObject(int layer) : id(nextID++), layer(layer) {}

void GameObject::Update(double deltaTime) {
    for (auto& [_, comp] : components) {
        comp->Update(deltaTime);
    }
}

int GameObject::GetID() const { return id; }

bool GameObject::operator<(const GameObject& g) const {
    if (layer == g.layer) {
        return id < g.id;
    }
    return layer < g.layer;
}

bool GameObject::operator<=(const GameObject& g) const {
    if (layer == g.layer) {
        return id <= g.id;
    }
    return layer <= g.layer;
}

bool GameObject::operator>=(const GameObject& g) const {
    if (layer == g.layer) {
        return id >= g.id;
    }
    return layer >= g.layer;
}

bool GameObject::operator>(const GameObject& g) const {
    if (layer == g.layer) {
        return id > g.id;
    }
    return layer > g.layer;
}

} // namespace OEngine