#include "TestScene.h"

#include "../src/IO/Keyboard.h"

void TestScene::Init() {
    s = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    s1 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 16, 16);
    s2 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    OEngine::EventManager::AddListener<ResetEvent>(&eventListener);
    OEngine::EventManager::AddListener<OEngine::KeyDownEvent>(&eventListener1);
    OEngine::Keyboard::Connect();
}

TestScene::~TestScene() {
    delete s;
    delete s1;
    delete s2;
    OEngine::EventManager::RemoveListener<ResetEvent>(&eventListener);
    OEngine::EventManager::RemoveListener<OEngine::KeyDownEvent>(&eventListener1);
    OEngine::Keyboard::Disconnect();
}

void TestScene::Update() {
    if (OEngine::Keyboard::IsPressed(OEngine::Key::Keycode::SPACE))
        spritePos += 5;

    s->UpdateOriginCenter(300, spritePos, 0);
    s1->UpdateOriginCenter(400, spritePos, 0);
    s2->UpdateOriginCenter(500, spritePos, 180);
    if (spritePos > 400) {
        OEngine::EventManager::AddEvent(ResetEvent());
    }
}

void TestScene::Render(OEngine::Renderer& renderer) {
    renderer.SetBackground(0, 92, 115, 255);
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.DrawRect(50, 50, 100, 200);
    renderer.FillRect(200, 50, 100, 200);

    renderer.RenderSprite(*s);
    renderer.RenderSprite(*s1);
    renderer.RenderSpriteWithRotation(*s2);
}

OEngine::EventType ResetEvent::GetType() const { return OEngine::EventType::CUSTOM; }

std::unique_ptr<OEngine::Event> ResetEvent::Clone() const {
    return std::make_unique<ResetEvent>(*this);
}
