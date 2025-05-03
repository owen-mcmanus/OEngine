/**
 * @file Component.h
 * @author Owen McManus
 * @date 2025/4/16
 */

#pragma once

namespace OEngine {

class GameObject;

class Component {
  public:
    virtual ~Component() = default;
    virtual void Update(double deltaTime) {};

    void SetOwner(GameObject* owner) { this->owner = owner; }

  protected:
    GameObject* owner = nullptr;
};
}; // namespace OEngine
