#include "../src/Core/Engine.h"
#include "../src/Core/Window.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace OEngine;

TEST(EngineTest, EngineInitialization) {
    EXPECT_NO_THROW({ Engine testEngine; });
}

TEST(EngineTest, CreateWindow) {
    Engine engine;
    Window& createWindow = engine.CreateWindow("test window", 200, 200, false);
    EXPECT_EQ(&createWindow, &engine.GetWindow());
}

TEST(EngineTest, GetWindowBeforeCreationThrowsError) {
    Engine engine;
    EXPECT_THROW({ engine.GetWindow(); }, std::runtime_error);
}
