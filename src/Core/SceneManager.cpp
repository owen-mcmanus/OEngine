#include "SceneManager.h"

#include <olog.h>

void SceneManager::SetActiveScene(Scene& scene, Renderer& renderer) {
    activeScene = std::ref(scene);
    scene.Init(renderer);
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