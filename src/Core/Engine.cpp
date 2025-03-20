#include "Engine.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <functional>
#include <iostream>
#include <olog.h>

using namespace OEngine;

Engine::Engine() : frameDelay(1000 / 60) {
    OLog::openLogFile("log.txt", OL_LOG_TO_STDOUT);
    OLog::log(OLog::INFO, "Starting Engine...");

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        OLog::log(OLog::CRITICAL, SDL_GetError());
        throw std::runtime_error("SDL_Init failed");
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        OLog::log(OLog::CRITICAL, IMG_GetError());
        throw std::runtime_error("IMG_Init failed");
    }

    OLog::log(OLog::INFO, "Engine Startup Complete");
}

Engine::Engine(const int fps) : Engine() { frameDelay = std::chrono::milliseconds(1000 / fps); }

Engine::~Engine() {
    OLog::log(OLog::INFO, "Starting Engine Cleanup...");
    AssetManager::TextureManager::ClearCache();
    SDL_Quit();
    IMG_Quit();
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
            window->GetRenderer().Clear();
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

Window& Engine::CreateWindow(const std::string& tite, int width, int height, bool fullscreen) {
    window = std::make_unique<Window>(tite, width, height, fullscreen);
    return *window;
}

Window& Engine::GetWindow() const { return *window; }

void Engine::SetActiveScene(Scene& scene) {
    // if (!window) {
    //     OLog::log(OLog::ERROR, "SetActiveScene: Window does not exist");
    //     throw std::runtime_error("Engine has no active window");
    // }
    sceneManager.SetActiveScene(scene);
}

void Engine::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        default:
            break;
        }
        window->HandleEvent(event);
    }
}
