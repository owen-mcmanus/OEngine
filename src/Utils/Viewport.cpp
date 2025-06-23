/**
 * @file Viewport.cpp
 * @author Owen McManus
 * @date 2025/9/23
 */

#include "Viewport.h"

#include "Events/EventManager.h"
#include "GameObjects/Camera.h"

using namespace OEngine;

glm::mat3 viewMatrix = glm::mat3(1.0f);
double viewRotation = 0.0f;
double viewScale = 1.0f;

EventListener<ChangeViewEvent> changeViewListener = [](const ChangeViewEvent& e) {
    viewMatrix = e.viewMatrix;
    viewRotation = e.rotation * 180.0 / M_PI;
    viewScale = e.scale;
};

static bool isConnected = false;

void Viewport::Connect() {
    if (!isConnected) {
        isConnected = true;
        EventManager::AddListener<ChangeViewEvent>(&changeViewListener);
    }
}

void Viewport::Disconnect() {
    isConnected = false;
    EventManager::RemoveListener<ChangeViewEvent>(&changeViewListener);
}

glm::vec2 Viewport::ScreenToWorld(float x, float y) {
    glm::vec3 screen{x, y, 1.0f};
    glm::vec3 world = glm::inverse(viewMatrix) * screen;
    return glm::vec2(world);
}

glm::vec2 Viewport::WorldToScreen(float x, float y) {
    glm::vec3 world{x, y, 1.0f};
    glm::vec3 screen = viewMatrix * world;
    return glm::vec2(screen);
}