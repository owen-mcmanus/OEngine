/**
 * @file Scene.cpp
 * @author Owen McManus
 * @date 2025/5/1
 */

#include "Scene.h"
#include "../Components/PrimitiveSprite.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "Renderer.h"

using namespace OEngine;

void Scene::Update(const double deltaTime) {
    PreUpdate(deltaTime);
    for (auto& object : activeGameObjects) {
        object->Update(deltaTime);
    }
    PostUpdate(deltaTime);
}

void Scene::Render(Renderer& renderer) {
    PreRender(renderer);
    for (auto& object : activeGameObjects) {
        if (object->HasComponent<Transform>() && object->HasComponent<Sprite>()) {
            renderer.RenderSpriteWithRotation(
                *object->GetComponent<Sprite>(), *object->GetComponent<Transform>());
        }
        if (object->HasComponent<Transform>() && object->HasComponent<PrimitiveSprite>()) {
            renderer.RenderPrimitiveSprite(
                *object->GetComponent<PrimitiveSprite>(), *object->GetComponent<Transform>());
        }
        if (object->HasComponent<Background>()) {
            renderer.RenderBackground(*object->GetComponent<Background>());
        }
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
