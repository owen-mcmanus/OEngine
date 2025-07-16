/**
 * @file Camera.h
 * @author Owen McManus
 * @date 2025/5/3
 */

#pragma once
#include "../Core/GameObject.h"
#include "../Events/Event.h"
#include "../Events/EventManager.h"
#include "glm/glm.hpp"

namespace OEngine {

class ChangeViewEvent : public Event {
  public:
    explicit ChangeViewEvent(const glm::mat3& viewMatrix, double rotation, double scale)
        : viewMatrix(viewMatrix), rotation(rotation), scale(scale) {};

    glm::mat3 viewMatrix;
    double rotation;
    double scale;
};

class CameraComponent : public Component {
  public:
    explicit CameraComponent(glm::vec2 position = {0, 0}, double rotation = 0, double zoom = 1);

    void SetViewMatrix();
    void SetZoom(double zoom);
    void ZoomAboutScreenPoint(double newZoom, glm::vec2 screen);
    [[nodiscard]] double GetZoom() const;
    void SetPosition(glm::vec2 position);
    glm::vec2 GetPosition();
    void Translate(glm::vec2 amount);
    void SetRotation(double rotation);
    [[nodiscard]] double GetRotation() const;
    void Rotate(double amount);
    void Update(double deltaTime) override;

  private:
    bool dirty = true;
    double zoom = 1;
    glm::vec2 offset = glm::vec2(0, 0);
    double rotation = 0;
};

class CameraController : public Component {
  public:
    CameraController();
    ~CameraController() override;
    void Update(double deltaTime) override;

  private:
    CameraComponent* t = nullptr;
    float wheelDelta = 0;
    EventListener<MouseScrolledEvent> mouseScrolledListener = [this](const MouseScrolledEvent& e) {
        this->wheelDelta = e.GetScroll();
    };
};

class Camera : public GameObject {
  public:
    explicit Camera(glm::vec2 pos, double rotation = 0);
};
} // namespace OEngine