#include "../src/Core/Engine.h"
#include "TestScene.h"

int main() {
    auto engine = OEngine::Engine();
    engine.CreateWindow("Game", 1920, 1080, false);
    OEngine::SceneManager::SetActiveScene(std::make_unique<TestScene>());
    engine.Run();
}