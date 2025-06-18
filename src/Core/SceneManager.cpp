/**
 * @file SceneManager.cpp
 * @author Owen McManus
 * @date 2025/6/18
 */

#include "SceneManager.h"

#include "Scene.h"

using namespace OEngine;

std::unique_ptr<Scene> SceneManager::activeScene = nullptr;

void SceneManager::SetActiveScene(std::unique_ptr<Scene>&& scene) {
    activeScene = std::move(scene);
    if (activeScene)
        activeScene->Init();
}

void SceneManager::Update(double deltaTime) {
    if (activeScene)
        activeScene->Update(deltaTime);
}

void SceneManager::Render(Renderer& renderer) {
    if (activeScene)
        activeScene->Render(renderer);
}

void SceneManager::ClearActiveScene() {
    activeScene.reset();
    activeScene = nullptr;
}