#include "Window.h"

#include <olog.h>

using namespace OEngine;

Window::Window(const std::string& title, int width, int height, bool fullscreen) {
    Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    if (fullscreen) {
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    SDL_Window* rawWindow = SDL_CreateWindow(
        title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    if (!rawWindow) {
        OLog::log(OLog::CRITICAL, SDL_GetError());
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }
    window.reset(rawWindow);

    renderer = std::make_unique<Renderer>(rawWindow);
}
Renderer& Window::GetRenderer() const { return *renderer; }

void Window::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_WINDOWEVENT) {
        switch (event.window.event) {
        case SDL_WINDOWEVENT_MINIMIZED:
            OLog::log(OLog::INFO, "Window rendering paused");
            renderer->Pause();
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            OLog::log(OLog::INFO, "Window maximized");
            break;
        case SDL_WINDOWEVENT_RESTORED:
            OLog::log(OLog::INFO, "Window rendering resumed");
            renderer->Resume();
            break;
        default:
            break;
        }
    }
}