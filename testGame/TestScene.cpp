#include "TestScene.h"

#include "../src/GameObjects/Camera.h"
#include "../src/IO/Keyboard.h"
#include "Plane.h"

void TestScene::Init() {
    std::shared_ptr<OEngine::GameObject> s = std::make_shared<Plane>(400, 300);
    std::shared_ptr<OEngine::GameObject> s2 = std::make_shared<Plane>(100, 300);

    std::shared_ptr<OEngine::Camera> c = std::make_shared<OEngine::Camera>(glm::vec2{0, 0}, 0);

    OEngine::Keyboard::Connect();
    OEngine::Mouse::Connect();

    AddGameObject(s);
    AddGameObject(s2);
    AddGameObject(c);
}

TestScene::~TestScene() {
    OEngine::Keyboard::Disconnect();
    OEngine::Mouse::Disconnect();
}

void TestScene::PreRender(OEngine::Renderer& renderer) {
    renderer.SetBackground(0, 92, 115, 255);
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.DrawRect(50, 50, 100, 200);
    renderer.FillRect(200, 50, 100, 200);
}
