/**
 * @file SceneManager.cpp
 * @author Owen McManus
 * @date 2025/6/18
 */

#include "SceneManager.h"

#include "Scene.h"
#include <olog.h>

using namespace OEngine;

std::unique_ptr<Scene> SceneManager::activeScene = nullptr;

void SceneManager::SetActiveScene(std::unique_ptr<Scene>&& scene) {
    activeScene = std::move(scene);
    if (activeScene)
        activeScene->Init();
}

void SceneManager::Update(double deltaTime) {
    try {
        if (activeScene)
            activeScene->Update(deltaTime);
    } catch (std::runtime_error& e) {
        if (e.what() != "change scene") {
            OLog::log(OLog::ERROR, std::string("Error: ") + e.what());
        }
    }
}

void SceneManager::Render(Renderer& renderer) {
    if (activeScene)
        activeScene->Render(renderer);
}

void SceneManager::ClearActiveScene() {
    activeScene.reset();
    activeScene = nullptr;
}