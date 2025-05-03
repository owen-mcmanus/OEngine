/**
 * @file Scene.cpp
 * @author Owen McManus
 * @date 2025/5/1
 */

#include "Scene.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "Renderer.h"

using namespace OEngine;

void Scene::Update(double deltaTime) {
    PreUpdate(deltaTime);
    for (auto& object : activeGameObjects) {
        object->Update(deltaTime);
    }
    PostUpdate(deltaTime);
}

void Scene::Render(Renderer& renderer) {
    PreRender(renderer);
    for (auto& object : activeGameObjects) {
        auto pos = object->GetComponent<OEngine::Transform>()->GetWorldPosition();
        object->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(pos.x, pos.y, 0);
        renderer.RenderSprite(*object->GetComponent<OEngine::Sprite>());
    }
    PostRender(renderer);
}

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