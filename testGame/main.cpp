#include "../src/Core/Engine.h"
#include "TestScene.h"

int main() {
    auto engine = OEngine::Engine();
    TestScene test;
    engine.CreateWindow("Game", 1920, 1080, false);
    OEngine::SceneManager::SetActiveScene(test);
    engine.Run();
}