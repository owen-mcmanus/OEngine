#include "SceneManager.h"

#include "Scene.h"

using namespace OEngine;

void SceneManager::SetActiveScene(Scene& scene) {
    activeScene = std::ref(scene);
    scene.Init();
}

void SceneManager::HandleEvents() {
    if (activeScene)
        activeScene->get().HandleEvents();
}

void SceneManager::Update() {
    if (activeScene)
        activeScene->get().Update();
}

void SceneManager::Render(Renderer& renderer) {
    if (activeScene) {
        activeScene->get().Render(renderer);
    }
}