/**
 * @file GameObject.h
 * @author Owen McManus
 * @date 2025/5/3
 */

#pragma once
#include "../Components/Component.h"
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace OEngine {

class GameObject {
  public:
    explicit GameObject(int layer = -1);
    virtual ~GameObject() = default;

    virtual void Update(double deltaTime);
    template <typename T, typename... Args> T& AddComponent(Args&&... args);
    template <typename T> T* GetComponent();
    template <typename T> std::weak_ptr<T> GetCacheableComponent();
    template <typename T> bool HasComponent() const;
    int GetID() const;

    bool operator<(const GameObject& g) const;
    bool operator<=(const GameObject& g) const;
    bool operator>=(const GameObject& g) const;
    bool operator>(const GameObject& g) const;
    int layer;

  private:
    int id;
    static int nextID;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
};

struct GameObjectComparator {
    bool
    operator()(const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) const {
        return *a < *b;
    }
};
} // namespace OEngine

#include "GameObject.tpp"