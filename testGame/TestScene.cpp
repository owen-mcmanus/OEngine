#include "TestScene.h"

#include "../src/IO/Keyboard.h"
#include "Plane.h"

void TestScene::Init() {
    std::shared_ptr<OEngine::GameObject> s = std::make_shared<Plane>(400, 300);
    // s1 = new OEngine::GameObject();
    std::shared_ptr<OEngine::GameObject> s2 = std::make_shared<Plane>(100, 0);
    s2->GetComponent<OEngine::Transform>()->SetParent(
        s->GetCacheableComponent<OEngine::Transform>());
    s2->GetComponent<OEngine::Transform>()->SetParent(std::weak_ptr<OEngine::Transform>());
    // s->AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    // s1->AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 16, 16);
    // s2->AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    // s = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    // s1 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 16, 16);
    // s2 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    // OEngine::EventManager::AddListener<OEngine::MouseButtonDownEvent>(&eventListener);
    // OEngine::EventManager::AddListener<OEngine::MouseScrolledEvent>(&eventListener2);

    OEngine::Keyboard::Connect();
    OEngine::Mouse::Connect();

    AddGameObject(s);
    AddGameObject(s2);
}

TestScene::~TestScene() {
    // delete s1;
    // OEngine::EventManager::RemoveListener<OEngine::MouseButtonDownEvent>(&eventListener);
    // OEngine::EventManager::RemoveListener<OEngine::MouseScrolledEvent>(&eventListener2);
    OEngine::Keyboard::Disconnect();
    OEngine::Mouse::Disconnect();
}

// void TestScene::Update() {
//     // if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::SPACE))
//     //     spritePos += 5;
//     // if (OEngine::Mouse::IsPressed(OEngine::Mouse::MouseButton::MIDDLE)) {
//     //     spritePos -= 5;
//     // }
//
//     // s->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(
//     //     OEngine::Mouse::GetX(), OEngine::Mouse::GetY(), 0);
//     // s1->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(400, spritePos, 0);
//     // s2->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(500, spritePos, 180);
//     // if (spritePos > 400) {
//     //     OEngine::EventManager::AddEvent(ResetEvent());
//     // }
//
//     for (auto& object : activeGameObjects) {
//         object->Update(0);
//     }
// }

void TestScene::PreRender(OEngine::Renderer& renderer) {
    renderer.SetBackground(0, 92, 115, 255);
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.DrawRect(50, 50, 100, 200);
    renderer.FillRect(200, 50, 100, 200);
}
