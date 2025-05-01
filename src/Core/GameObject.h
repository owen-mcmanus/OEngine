/**
 * @file GameObject.h
 * @author Owen McManus
 * @date 2025/4/16
 */

#pragma once
#include "../Components/Component.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace OEngine {

class GameObject {
  public:
    GameObject();
    virtual ~GameObject() = default;

    void Update(float deltaTime);
    template <typename T, typename... Args> T& AddComponent(Args&&... args);
    template <typename T> T* GetComponent();
    template <typename T> std::weak_ptr<T> GetCacheableComponent();
    template <typename T> bool HasComponent() const;
    int GetID() const;

  private:
    int id;
    static int nextID;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};
} // namespace OEngine

#include "GameObject.tpp"