/**
 * @file GameObject.tpp
 * @author Owen McManus
 * @date 2025/5/1
 */
#pragma once

namespace OEngine {
template <typename T, typename... Args> T& GameObject::AddComponent(Args&&... args) {
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T& ref = *component;
    components[std::type_index(typeid(T))] = std::unique_ptr<Component>(std::move(component));
    ref.SetOwner(this);
    return ref;
}

template <typename T> T* GameObject::GetComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}

template <typename T> std::weak_ptr<T> GameObject::GetCacheableComponent() {
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    auto it = components.find(std::type_index(typeid(T)));
    if (it != components.end()) {
        return std::dynamic_pointer_cast<T>(it->second);
    }
    return {};
}

template <typename T> bool GameObject::HasComponent() const {
    return components.contains(std::type_index(typeid(T)));
}
} // namespace OEngine