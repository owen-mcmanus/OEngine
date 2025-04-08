#include "../src/Core/Engine.h"
#include "TestScene.h"

#include <iostream>
#include <ostream>

int main() {
    TestScene test;
    auto engine = OEngine::Engine();
    engine.CreateWindow("Game", 1920, 1080, false);
    engine.SetActiveScene(test);
    engine.Run();
}