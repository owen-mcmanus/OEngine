/**
 * @file SceneManager.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "SceneManager.h"

#include "Scene.h"

using namespace OEngine;

void SceneManager::SetActiveScene(Scene& scene) {
    activeScene = std::ref(scene);
    scene.Init();
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