#include "TestScene.h"

#include "../src/IO/Keyboard.h"

void TestScene::Init() {
    s = new OEngine::GameObject();
    s1 = new OEngine::GameObject();
    s2 = new OEngine::GameObject();
    s->AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    s1->AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 16, 16);
    s2->AddComponent<OEngine::Sprite>("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    // s = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    // s1 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 16, 16);
    // s2 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    OEngine::EventManager::AddListener<OEngine::MouseButtonDownEvent>(&eventListener);
    OEngine::EventManager::AddListener<OEngine::MouseScrolledEvent>(&eventListener2);

    OEngine::Keyboard::Connect();
    OEngine::Mouse::Connect();
}

TestScene::~TestScene() {
    delete s;
    delete s1;
    delete s2;
    OEngine::EventManager::RemoveListener<OEngine::MouseButtonDownEvent>(&eventListener);
    OEngine::EventManager::RemoveListener<OEngine::MouseScrolledEvent>(&eventListener2);
    OEngine::Keyboard::Disconnect();
    OEngine::Mouse::Disconnect();
}

void TestScene::Update() {
    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::SPACE))
        spritePos += 5;
    if (OEngine::Mouse::IsPressed(OEngine::Mouse::MouseButton::MIDDLE)) {
        spritePos -= 5;
    }

    s->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(
        OEngine::Mouse::GetX(), OEngine::Mouse::GetY(), 0);
    s1->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(400, spritePos, 0);
    s2->GetComponent<OEngine::Sprite>()->UpdateOriginCenter(500, spritePos, 180);
    if (spritePos > 400) {
        OEngine::EventManager::AddEvent(ResetEvent());
    }
}

void TestScene::Render(OEngine::Renderer& renderer) {
    renderer.SetBackground(0, 92, 115, 255);
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.DrawRect(50, 50, 100, 200);
    renderer.FillRect(200, 50, 100, 200);

    renderer.RenderSprite(*s->GetComponent<OEngine::Sprite>());
    renderer.RenderSprite(*s1->GetComponent<OEngine::Sprite>());
    renderer.RenderSpriteWithRotation(*s2->GetComponent<OEngine::Sprite>());
}

OEngine::EventType ResetEvent::GetType() const { return OEngine::EventType::CUSTOM; }

std::unique_ptr<OEngine::Event> ResetEvent::Clone() const {
    return std::make_unique<ResetEvent>(*this);
}
