/**
 * @file Engine.cpp
 * @author Owen McManus
 * @date 2025/4/9
 */

#include "Engine.h"

#include "../AssetManager/TextureManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Window.h"

#include <SDL3/SDL.h>
#include <chrono>
#include <olog.h>
#include <stdexcept>
#include <string>

using namespace OEngine;

Engine::Engine() {
    OLog::openLogFile("log.txt", OLog::OL_LOG_TO_STDOUT);
    OLog::log(OLog::INFO, "Starting Engine...");

    if (!SDL_SetAppMetadata("OEngine", "0.1.0", "oengine.test")) {
        OLog::log(OLog::ERROR, SDL_GetError());
    }

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        OLog::log(OLog::CRITICAL, SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }

    OLog::log(OLog::INFO, "Engine Startup Complete");
}

Engine::~Engine() {
    OLog::log(OLog::INFO, "Starting Engine Cleanup...");
    window.reset();
    AssetManager::TextureManager::ClearCache();
    SDL_Quit();
    OLog::log(OLog::INFO, "Engine Cleanup Complete");
    OLog::closeLogFile();
}

void Engine::Run() {
    running = true;
    OLog::log(OLog::INFO, "Starting Game Loop...");

    while (running) {
        const std::chrono::milliseconds frameStart(SDL_GetTicks());

        // handle events
        HandleEvents();
        // update
        sceneManager.Update();

        // render
        if (window) {
            sceneManager.Render(window->GetRenderer());
            window->GetRenderer().Present();
        }

        // Calculate the time spent during the current frame
        const std::chrono::milliseconds frameTime(SDL_GetTicks() - frameStart.count());

        // If the frame took less time than the desired delay, delay the rest of the frame
        if (frameTime.count() < frameDelay.count()) {
            SDL_Delay(frameDelay.count() - frameTime.count());
        }
    }
    OLog::log(OLog::INFO, "Game Loop Complete");
}

Window& Engine::CreateWindow(const std::string& title, int width, int height, bool fullscreen) {
    window = std::make_unique<Window>(title, width, height, fullscreen);
    return *window;
}

Window& Engine::GetWindow() const {
    if (!window) {
        OLog::log(OLog::ERROR, "GetWindow: Window does not exist");
        throw std::runtime_error("Window does not exist");
    }
    return *window;
}

void Engine::SetActiveScene(Scene& scene) { sceneManager.SetActiveScene(scene); }

void Engine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) { // TODO: consider SDL_WaitEvent
        switch (event.type) {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        default:
            break;
        }
        if (window)
            window->HandleEvent(event);
    }
}
