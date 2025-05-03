/**
 * @file SceneManager.cpp
 * @author Owen McManus
 * @date 2025/4/12
 */

#include "SceneManager.h"

#include "Scene.h"

#include <iostream>

using namespace OEngine;

void SceneManager::SetActiveScene(Scene& scene) {
    activeScene = std::ref(scene);
    scene.Init();
}

void SceneManager::Update(double deltaTime) const {
    if (activeScene)
        activeScene->get().Update(deltaTime);
}

void SceneManager::Render(Renderer& renderer) const {
    if (activeScene) {
        activeScene->get().Render(renderer);
    }
}