#include "../src/Core/Engine.h"
#include "TestScene.h"

#include <iostream>
#include <ostream>

int main() {
    auto engine = OEngine::Engine();
    TestScene test;
    engine.CreateWindow("Game", 1920, 1080, false);
    engine.SetActiveScene(test);
    engine.Run();
}