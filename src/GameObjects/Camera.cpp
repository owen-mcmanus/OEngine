/**
 * @file Camera.cpp
 * @author Owen McManus
 * @date 2025/5/3
 */

#include "Camera.h"
#include "../Components/Transform.h"
#include "../Events/EventManager.h"
#include "../IO/Keyboard.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "Utils/Viewport.h"
#include "glm/gtx/matrix_transform_2d.hpp"
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace OEngine;

// void CameraController::Update(double deltaTime) {
//     if (t == nullptr)
//         t = owner->GetComponent<CameraComponent>();
//     if (Keyboard::IsPressed(Key::Keycode::W))
//         t->Translate(glm::vec2(0.0f, -200.0f * deltaTime));
//     if (Keyboard::IsPressed(Key::Keycode::S))
//         t->Translate(glm::vec2(0.0f, 200.0f * deltaTime));
//     if (Keyboard::IsPressed(Key::Keycode::A))
//         t->Translate(glm::vec2(-200.0f * deltaTime, 0.0f));
//     if (Keyboard::IsPressed(Key::Keycode::D))
//         t->Translate(glm::vec2(200.0f * deltaTime, 0.0f));
//     if (Keyboard::IsPressed(Key::Keycode::Q))
//         t->Rotate(2 * 3.14 * deltaTime);
//     if (Keyboard::IsPressed(Key::Keycode::E))
//         t->Rotate(-2 * 3.14 * deltaTime);
// }

CameraController::CameraController() {
    EventManager::AddListener<MouseScrolledEvent>(&mouseScrolledListener);
}

CameraController::~CameraController() {
    EventManager::RemoveListener<MouseScrolledEvent>(&mouseScrolledListener);
}

void CameraController::Update(double dt) {
    if (t == nullptr)
        t = owner->GetComponent<CameraComponent>();

    static float lastX = Mouse::GetX();
    static float lastY = Mouse::GetY();

    float curX = Mouse::GetX();
    float curY = Mouse::GetY();

    glm::vec2 deltaScreen(curX - lastX, curY - lastY);

    lastX = curX;
    lastY = curY;

    if (Keyboard::IsPressed(Key::Keycode::Q))
        t->Rotate(2 * 3.14 * dt);
    if (Keyboard::IsPressed(Key::Keycode::E))
        t->Rotate(-2 * 3.14 * dt);

    bool dragging = Mouse::IsPressed(Mouse::MouseButton::RIGHT);

    if (dragging && deltaScreen != glm::vec2(0.0f)) {
        float zoom = t->GetZoom();         // current camera zoom
        float rotation = t->GetRotation(); // radians, CCW-positive

        glm::vec2 deltaWorld = glm::rotate(-deltaScreen / zoom, rotation);
        t->Translate(deltaWorld);
    }

    // ReSharper disable once CppDFAConstantConditions
    if (wheelDelta != 0.0f) {
        const float zoomStep = 0.1f;
        float z = t->GetZoom() * (1.0f + wheelDelta * zoomStep);
        // t->SetZoom(std::max(0.01f, z), {OEngine::Mouse::GetX(), OEngine::Mouse::GetY()});
        t->ZoomAboutScreenPoint(
            std::max(0.01f, z), {OEngine::Mouse::GetX(), OEngine::Mouse::GetY()});
        wheelDelta = 0.0f;
    }
}

Camera::Camera(glm::vec2 pos, double rotation) { AddComponent<CameraComponent>(pos, rotation); }

CameraComponent::CameraComponent(glm::vec2 position, double rotation, double zoom)
    : zoom(zoom), offset(position), rotation(rotation) {}

void CameraComponent::SetViewMatrix() {
    glm::vec2 pivot = glm::vec2{1920 * .5f, 1080 * .5f};
    glm::mat3 view(1.0f);
    view = glm::translate(view, (pivot));
    view = glm::scale(view, glm::vec2(zoom));
    view = glm::rotate(view, static_cast<float>(-rotation));
    view = glm::translate(view, -offset);
    ChangeViewEvent e = ChangeViewEvent(view, rotation, zoom);
    EventManager::DispatchEvent(e);
    // EventManager::AddEvent<ChangeViewEvent>(view, rotation);
}

void CameraComponent::ZoomAboutScreenPoint(double newZoom, glm::vec2 screen) {
    const glm::vec2 centre{1920 * 0.5f, 1080 * 0.5f};

    const double oldZoom = zoom;
    zoom = std::max(0.01, newZoom); // keep > 0

    // delta = (screen-centre vector) * (1/oldZoom − 1/newZoom), then un-rotate
    glm::vec2 vScreen = screen - centre;
    glm::vec2 delta = glm::rotate(
        vScreen * float(1.0 / oldZoom - 1.0 / zoom),
        float(rotation)); // rotation in *radians*
    offset += delta;      // pan so the world pt under the cursor is fixed
    dirty = true;
}

void CameraComponent::SetZoom(double zoom) {
    dirty = true;
    ZoomAboutScreenPoint(zoom, {1920 * 0.5f, 1080 * 0.5f});
    this->zoom = zoom;
}

double CameraComponent::GetZoom() const { return zoom; }

void CameraComponent::SetPosition(glm::vec2 position) {
    dirty = true;
    this->offset = position;
}

glm::vec2 CameraComponent::GetPosition() { return offset; }

void CameraComponent::Translate(glm::vec2 amount) {
    dirty = true;
    this->offset += amount;
}

void CameraComponent::SetRotation(double rotation) {
    dirty = true;
    this->rotation = rotation;
}

double CameraComponent::GetRotation() const { return rotation; }

void CameraComponent::Rotate(double amount) {
    dirty = true;
    this->rotation += amount;
}

void CameraComponent::Update(double deltaTime) {
    if (dirty) {
        SetViewMatrix();
        dirty = false;
    }
}
