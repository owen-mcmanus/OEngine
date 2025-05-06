#include "TestScene.h"

#include "../src/Components/PrimitiveSprite.h"
#include "../src/GameObjects/Camera.h"
#include "../src/IO/Keyboard.h"
#include "Plane.h"

void TestScene::Init() {
    std::shared_ptr<OEngine::GameObject> s = std::make_shared<Plane>(400, 300);
    std::shared_ptr<OEngine::GameObject> s2 = std::make_shared<Plane>(100, 300);

    std::shared_ptr<OEngine::Camera> c = std::make_shared<OEngine::Camera>(glm::vec2{0, 0}, 0);

    std::shared_ptr<OEngine::GameObject> box = std::make_shared<OEngine::GameObject>(13);
    std::shared_ptr<OEngine::GameObject> box1 = std::make_shared<OEngine::GameObject>(13);

    box->AddComponent<OEngine::PrimitiveSprite>(
        OEngine::PrimitiveSpriteType::FILL_RECTANGLE, OEngine::Color::Black, 100, 200);
    box->AddComponent<OEngine::Transform>(50, 50);

    box1->AddComponent<OEngine::PrimitiveSprite>(
        OEngine::PrimitiveSpriteType::FILL_RECTANGLE, OEngine::Color::Black, 100, 200);
    box1->AddComponent<OEngine::Transform>(200, 50);

    std::shared_ptr<OEngine::GameObject> background = std::make_shared<OEngine::GameObject>(0);
    background->AddComponent<OEngine::Background>(OEngine::Color::fromBytes(0, 92, 115, 255));

    OEngine::Keyboard::Connect();
    OEngine::Mouse::Connect();

    AddGameObject(s);
    AddGameObject(s2);
    AddGameObject(box);
    AddGameObject(box1);
    AddGameObject(background);
    AddGameObject(c);
}

TestScene::~TestScene() {
    OEngine::Keyboard::Disconnect();
    OEngine::Mouse::Disconnect();
}