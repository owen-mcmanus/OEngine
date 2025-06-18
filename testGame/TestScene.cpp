#include "TestScene.h"

#include "../src/Components/PrimitiveSprite.h"
#include "../src/GameObjects/Camera.h"
#include "../src/GameObjects/PrimitiveFactory.h"
#include "../src/IO/Keyboard.h"
#include "../src/UI/Objects/Button.h"
#include "Plane.h"

void TestScene::Init() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::shared_ptr<OEngine::GameObject> s = std::make_shared<Plane>(40 * i, 40 * j);
            AddGameObject(s);
        }
    }

    auto c = std::make_shared<OEngine::Camera>(glm::vec2{0, 0}, 0);

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

    AddGameObject(box);
    AddGameObject(box1);
    AddGameObject(background);
    AddGameObject(c);
    AddGameObject(c);
    AddGameObject(button);
    AddGameObject(text);
}

TestScene::~TestScene() {
    OEngine::Keyboard::Disconnect();
    OEngine::Mouse::Disconnect();
}

GrowAnimation::GrowAnimation() {
    const std::vector<OEngine::KeyFrame> keys = {
        {0, 100, OEngine::AnimationCurve::easeInOut, 1},
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
