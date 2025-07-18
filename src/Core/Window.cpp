/**
 * @file Window.cpp
 * @author Owen McManus
 * @date 2025/9/4
 */

#include "Window.h"

#include "Renderer.h"

#include <olog.h>

using namespace OEngine;

Window::Window(const std::string& title, int width, int height, bool fullscreen) {
    SDL_WindowFlags windowFlags = SDL_WINDOW_RESIZABLE;
    if (fullscreen) {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }

    SDL_Window* rawWindow;
    SDL_Renderer* rawRenderer;
    if (!SDL_CreateWindowAndRenderer(
            title.c_str(), width, height, windowFlags, &rawWindow, &rawRenderer)) {
        OLog::log(OLog::CRITICAL, SDL_GetError());
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }
    window.reset(rawWindow);

    renderer = std::make_unique<Renderer>(rawRenderer);
    windowInstance = window.get();
}

SDL_Window* Window::windowInstance = nullptr;

SDL_Window* Window::GetSDLWindow() { return windowInstance; }

Renderer& Window::GetRenderer() const { return *renderer; }

void Window::HandleEvent(const SDL_Event& event) {
    // if (event.type == SDL_WINDOWEVENT) {
    switch (event.type) {
    case SDL_EVENT_WINDOW_MINIMIZED:
        OLog::log(OLog::INFO, "Window rendering paused");
        renderer->Pause();
        break;
    case SDL_EVENT_WINDOW_MAXIMIZED:
        OLog::log(OLog::INFO, "Window maximized");
        break;
    case SDL_EVENT_WINDOW_RESTORED:
        OLog::log(OLog::INFO, "Window rendering resumed");
        renderer->Resume();
        break;
    default:
        break;
    }
    // }
}