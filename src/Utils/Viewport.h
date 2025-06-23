/**
 * @file Viewport.h
 * @author Owen McManus
 * @date 2025/9/23
 */

#pragma once
#include <glm/vec2.hpp>

namespace OEngine::Viewport {

enum class MouseButton { LEFT = 1, MIDDLE = 2, RIGHT = 3 };
void Connect();
void Disconnect();
glm::vec2 ScreenToWorld(float x, float y);
glm::vec2 WorldToScreen(float x, float y);

} // namespace OEngine::Viewport
