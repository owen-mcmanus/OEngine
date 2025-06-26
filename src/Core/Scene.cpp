/**
 * @file Scene.cpp
 * @author Owen McManus
 * @date 2025/5/1
 */

#include "Scene.h"
#include "../Components/PrimitiveSprite.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "Components/MultiSprite.h"
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
        if (object->layer == -1)
            continue;
        if (object->layer == 0 && object->HasComponent<Background>()) {
            renderer.RenderBackground(*object->GetComponent<Background>());
            continue;
        }

        bool inWorld = true;
        if (object->layer >= 100)
            inWorld = false;
        if (object->HasComponent<Transform>() && object->HasComponent<MultiSprite>()) {
            const MultiSprite* ms = object->GetComponent<MultiSprite>();
            int sI = 0;
            int psI = 0;
            while (sI < ms->GetNumSprites() || psI < ms->GetNumPrimitiveSprites()) {
                if (sI < ms->GetNumSprites() && psI < ms->GetNumPrimitiveSprites()) {
                    if (ms->GetSpriteLayer(sI) < ms->GetPrimitiveSpriteLayer(psI)) {
                        renderer.RenderSpriteWithRotation(
                            *ms->GetSprite(sI), *ms->GetSpriteOffset(sI), inWorld);
                        sI++;
                    } else {
                        renderer.RenderPrimitiveSprite(
                            *ms->GetPrimitiveSprite(psI), *ms->GetPrimitiveSpriteOffset(psI),
                            inWorld);
                        psI++;
                    }
                } else if (sI < ms->GetNumSprites()) {
                    renderer.RenderSpriteWithRotation(
                        *ms->GetSprite(sI), *ms->GetSpriteOffset(sI), inWorld);
                    sI++;
                } else {
                    renderer.RenderPrimitiveSprite(
                        *ms->GetPrimitiveSprite(psI), *ms->GetPrimitiveSpriteOffset(psI), inWorld);
                    psI++;
                }
            }
        }
        if (object->HasComponent<Transform>() && object->HasComponent<Sprite>()) {
            renderer.RenderSpriteWithRotation(
                *object->GetComponent<Sprite>(), *object->GetComponent<Transform>(), inWorld);
        }
        if (object->HasComponent<Transform>() && object->HasComponent<PrimitiveSprite>()) {
            renderer.RenderPrimitiveSprite(
                *object->GetComponent<PrimitiveSprite>(), *object->GetComponent<Transform>(),
                inWorld);
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
