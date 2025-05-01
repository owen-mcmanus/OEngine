/**
 * @file Scene.cpp
 * @author Owen McManus
 * @date 2025/5/1
 */

#include "Scene.h"

using namespace OEngine;

void Scene::AddGameObject(const std::shared_ptr<GameObject>& gameObject) {
    activeGameObjects.insert(gameObject);
}

void Scene::RemoveGameObject(GameObject* ptr) {
    auto it = std::find_if(
        activeGameObjects.begin(), activeGameObjects.end(),
        [ptr](const std::shared_ptr<GameObject>& p) { return p.get() == ptr; });
    if (it != activeGameObjects.end())
        activeGameObjects.erase(it);
}