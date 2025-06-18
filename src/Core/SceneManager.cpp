/**
 * @file SceneManager.cpp
 * @author Owen McManus
 * @date 2025/6/17
 */

#include "SceneManager.h"

#include "Scene.h"

using namespace OEngine;

std::optional<std::reference_wrapper<Scene>> SceneManager::activeScene;

void SceneManager::SetActiveScene(Scene& scene) {
    activeScene = std::ref(scene);
    scene.Init();
}

void SceneManager::Update(double deltaTime) {
    if (activeScene)
        activeScene->get().Update(deltaTime);
}

void SceneManager::Render(Renderer& renderer) {
    if (activeScene)
        activeScene->get().Render(renderer);
}