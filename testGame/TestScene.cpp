#include "TestScene.h"

#include "../src/GameObjects/Camera.h"
#include "../src/GameObjects/PrimitiveFactory.h"
#include "../src/IO/Keyboard.h"
#include "../src/UI/Objects/Button.h"
#include "Components/Delay.h"
#include "Components/MultiSprite.h"
#include "Plane.h"

void TestScene::Init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::shared_ptr<OEngine::GameObject> s = std::make_shared<Plane>(40 * i, 40 * j);
            AddGameObject(s);
        }
    }

    auto c = std::make_shared<OEngine::Camera>(glm::vec2{0, 0}, 0);
    c->AddComponent<OEngine::CameraController>();

    std::shared_ptr<OEngine::GameObject> box =
        OEngine::PrimitiveFactory::CreateRectangle(50, 50, 100, 200, OEngine::Color::Black, 13);
    box->AddComponent<GrowAnimation>();
    box->GetComponent<GrowAnimation>()->StartAnimation();

    std::shared_ptr<OEngine::GameObject> box1 = OEngine::PrimitiveFactory::CreateFilledRectangle(
        200, 50, 100, 200, OEngine::Color::Black, 13);

    std::shared_ptr<OEngine::GameObject> background =
        OEngine::PrimitiveFactory::CreateBackground(OEngine::Color::fromBytes(0, 92, 115, 255));

    std::shared_ptr<OEngine::UI::Button> button =
        std::make_shared<OEngine::UI::Button>("rotate", 0, 50, 100, 50);

    std::shared_ptr<OEngine::GameObject> text = std::make_shared<OEngine::GameObject>(3);
    text->AddComponent<OEngine::Sprite>(
        "/home/owen/github/OEngine/testGame/VRC.ttf", 50, "test\n text!", OEngine::Color::Red);
    text->AddComponent<OEngine::Transform>(0, 0);

    OEngine::Keyboard::Connect();
    OEngine::Mouse::Connect();

    OEngine::Mouse::SetCursor("/home/owen/github/Scopes/Assets/Cursors/AsdexFixed.cur");

    auto testMulti = std::make_shared<OEngine::GameObject>(5);
    testMulti->AddComponent<OEngine::Transform>(600, 600);
    OEngine::MultiSprite& ms = testMulti->AddComponent<OEngine::MultiSprite>();
    ms.AddSprite(
        std::make_unique<OEngine::Sprite>(
            "/home/owen/github/OEngine/testGame/VRC.ttf", 50, "test\n text!", OEngine::Color::Red),
        {0, 0}, 2);
    ms.AddSprite(
        std::make_unique<OEngine::Sprite>(
            "/home/owen/github/OEngine/testGame/VRC.ttf", 50, "test\n text!", OEngine::Color::Red),
        {20, 20});
    ms.AddPrimitiveSprite(
        std::make_unique<OEngine::PrimitiveSprite>(
            OEngine::PrimitiveSpriteType::FILL_RECTANGLE, OEngine::Color::Black, 50, 50),
        {50, 50}, 1);

    auto line = OEngine::PrimitiveFactory::CreateLine(1000, 1000, 10, 10, OEngine::Color::Black, 5);

    AddGameObject(box);
    AddGameObject(box1);
    AddGameObject(background);
    AddGameObject(c);
    AddGameObject(button);
    AddGameObject(text);
    AddGameObject(testMulti);
    AddGameObject(line);
}

TestScene::~TestScene() {
    OEngine::Keyboard::Disconnect();
    OEngine::Mouse::Disconnect();
}

GrowAnimation::GrowAnimation() {
    const std::vector<OEngine::KeyFrame> keys = {
        {0, 100, OEngine::AnimationCurve::spring, 1},
        {2000, 500, OEngine::AnimationCurve::linear, 1}};
    AddKeyFrame(keys);
}

void GrowAnimation::HandleFrame(std::vector<OEngine::KeyFrame> keys) {
    for (auto key : keys) {
        if (key.keyId == 1) {
            auto t = owner->GetComponent<OEngine::Transform>();
            t->localPosition.x = key.value;
        }
    }
}
