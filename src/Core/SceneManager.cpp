/**
 * @file SceneManager.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "SceneManager.h"

#include "Scene.h"

using namespace OEngine;

void SceneManager::SetActiveScene(Scene& scene) {
    activeScene = std::ref(scene);
    scene.Init();
}

void SceneManager::HandleEvents() const {
    if (activeScene)
        activeScene->get().HandleEvents();
}

void SceneManager::Update() const {
    if (activeScene)
        activeScene->get().Update();
}

void SceneManager::Render(Renderer& renderer) const {
    if (activeScene) {
        activeScene->get().Render(renderer);
    }
}