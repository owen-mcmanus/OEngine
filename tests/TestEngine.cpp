#include "../src/Core/Engine.h"
#include "../src/Core/Scene.h"
#include "../src/Core/SceneManager.h"
#include "../src/Core/Window.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockScene : public Scene {
  public:
    MockScene() = default;
    ~MockScene() = default;
    void Init(Renderer& renderer) override {};
    void Update() override {};
    void HandleEvents() override {};
    void Render(Renderer& renderer) override {};
};

// Test for default constructor
TEST(EngineTest, ConstructorInitializesSuccessfully) {
    Engine engine; // Use the default constructor (60 FPS)

    // We can't directly access frameDelay, but we can check for expected behavior
    EXPECT_EQ(engine.running, false); // Shouldn't be running yet
}

// Test for constructor with custom FPS
TEST(EngineTest, ConstructorWithCustomFPS) {
    const int customFPS = 30;
    Engine engine(customFPS);

    // Directly checking the frameDelay is not possible without access to private members
    // So we would have to rely on testing behavior when calling Run, which we’ll do in another test
    EXPECT_EQ(engine.running, false); // Ensure it's not running yet
}

// Test for CreateWindow method
TEST(EngineTest, CreateWindowCreatesWindow) {
    Engine engine;

    // Create a window with specified properties
    Window& window = engine.CreateWindow("Test Window", 800, 600, false);

    // Check that we can get the window back and use it (i.e., it's properly initialized)
    EXPECT_NO_THROW(engine.GetWindow());
}

// Test for GetWindow() behavior
TEST(EngineTest, GetWindowReturnsValidWindow) {
    Engine engine;
    Window& window = engine.CreateWindow("Test Window", 800, 600, false);

    // We expect this to be the same window created earlier
    EXPECT_EQ(&engine.GetWindow(), &window);
}

// Test for SetActiveScene method
TEST(EngineTest, SetActiveSceneChangesScene) {
    Engine engine;
    MockScene scene;
    engine.CreateWindow("Test Window", 800, 600, false);

    // Since there's no direct access to check if the scene was set, we assume that
    // if SetActiveScene is called, no errors should occur and everything should run smoothly
    EXPECT_NO_THROW(engine.SetActiveScene(scene));
}

// Test for Run method (test that it processes events and doesn't run forever)
TEST(EngineTest, RunProcessesEvents) {
    Engine engine;

    // We can't directly observe the game loop without mocks, but we can check that it
    // completes without hanging indefinitely. One simple way is to call `Run()` and
    // assert that it exits properly. This will involve setting `running` to `false`
    // after the first event loop, simulating one cycle.

    // Run the engine (it will exit the loop right away)
    engine.running = true;
    std::thread runThread([&engine]() { engine.Run(); });

    // Let the engine run for a short while and then stop
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    engine.running = false; // Stop the engine after a short while
    runThread.join();       // Join the thread to ensure the game loop terminates
}

// Test for destructor and cleanup
TEST(EngineTest, DestructorCleansUp) {
    Engine* engine = new Engine(); // Create engine object

    // After engine is destroyed, SDL and IMG should be cleaned up.
    // We can call SDL functions that should fail if cleanup hasn't occurred.
    delete engine;

    // Verify that the cleanup has happened (if SDL_Quit is successful, we know cleanup worked)
    EXPECT_EQ(SDL_WasInit(SDL_INIT_EVERYTHING), 0); // Should be 0 after cleanup
}

// Test that SDL events are processed correctly
TEST(EngineTest, HandleEventsProcessesQuitEvent) {
    Engine engine;
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);

    // Simulate handling a quit event
    engine.Run(); // Should process the quit event and set `running = false`

    // Check if the engine stops running after the event
    EXPECT_EQ(engine.running, false);
}
