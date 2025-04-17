/**
 * @file Mouse.h
 * @author Owen McManus
 * @date 2025/4/16
 */

#pragma once
#include <vector>

namespace OEngine::Mouse {

enum class MouseButton { LEFT = 1, MIDDLE = 2, RIGHT = 3 };
void Connect();
void Disconnect();
std::vector<MouseButton> GetPressed();
bool IsPressed(MouseButton key);
float GetX();
float GetY();

} // namespace OEngine::Mouse
