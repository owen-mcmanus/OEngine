/**
 * @file Screen.cpp
 * @author Owen McManus
 * @date 2025/5/16
 */

#include "Screen.h"
#include "../Events/Event.h"
#include "../Events/EventManager.h"

using namespace OEngine;

static int width = 1920;
static int height = 1080;

EventListener<WindowResizeEvent> windowResizeListener = [](const WindowResizeEvent& e) {
    width = e.width;
    height = e.height;
};
static bool isConnected = false;

void Screen::Connect() {
    if (!isConnected) {
        isConnected = true;
        EventManager::AddListener<WindowResizeEvent>(&windowResizeListener);
    }
}

void Screen::Disconnect() {
    isConnected = false;
    EventManager::RemoveListener<WindowResizeEvent>(&windowResizeListener);
    width = 1920;
    height = 1080;
}

float Screen::GetWidth() { return width; }

float Screen::GetHeight() { return height; }
