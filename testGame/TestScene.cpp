#include "TestScene.h"

void TestScene::Init() {
    s = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
    s1 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 16, 16);
    s2 = new OEngine::Sprite("/home/owen/github/OEngine/testGame/plane.png", 32, 32);
}

TestScene::~TestScene() {
    delete s;
    delete s1;
    delete s2;
}

void TestScene::Update() { return; }

void TestScene::HandleEvents() { return; }

void TestScene::Render(OEngine::Renderer& renderer) {

    renderer.SetBackground(0, 92, 115, 255);
    renderer.SetDrawColor(0, 0, 0, 255);
    renderer.DrawRect(50, 50, 100, 200);
    renderer.FillRect(200, 50, 100, 200);

    s->UpdateOriginCenter(300, 300, 0);
    s1->UpdateOriginCenter(400, 300, 0);
    s2->UpdateOriginCenter(500, 300, 180);

    renderer.RenderSprite(*s);
    renderer.RenderSprite(*s1);
    renderer.RenderSpriteWithRotation(*s2);
}
