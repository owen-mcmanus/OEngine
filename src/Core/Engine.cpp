/**
 * @file Engine.cpp
 * @author Owen McManus
 * @date 2025/4/11
 */

#include "Engine.h"

#include "../AssetManager/TextureManager.h"
#include "AssetManager/FontManager.h"
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

    if (!TTF_Init()) {
        OLog::log(OLog::CRITICAL, SDL_GetError());
        throw std::runtime_error("TTF_Init failed");
    }

    EventManager::AddListener<QuitEvent>(&eventListener);

    OLog::log(OLog::INFO, "Engine Startup Complete");
}

Engine::~Engine() {
    OLog::log(OLog::INFO, "Starting Engine Cleanup...");
    SceneManager::ClearActiveScene();
    window.reset();
    EventManager::RemoveListener<QuitEvent>(&eventListener);
    AssetManager::TextureManager::ClearCache();
    AssetManager::FontManager::ClearCache();
    TTF_Quit();
    SDL_Quit();
    OLog::log(OLog::INFO, "Engine Cleanup Complete");
    OLog::closeLogFile();
}

void Engine::Run() {
    running = true;
    OLog::log(OLog::INFO, "Starting Game Loop...");

    // int frameCount = 0;
    // Uint64 timeAccumulator = 0;

    Uint64 lastTime = 0;

    while (running) {
        Uint32 frameStart = SDL_GetTicks();

        EventManager::HandleEvents();

        Uint64 currentTime = SDL_GetPerformanceCounter();
        SceneManager::Update(
            std::min(
                static_cast<double>(currentTime - lastTime) / SDL_GetPerformanceFrequency(), 0.5));
        lastTime = currentTime;

        if (window) {
            SceneManager::Render(window->GetRenderer());
            window->GetRenderer().Present();
        }

        // Uint32 frameTime = SDL_GetTicks() - frameStart;

        // If the frame took less time than the desired delay, delay the rest of the frame
        // if (frameTime < frameDelay) {
        // SDL_Delay(frameDelay - frameTime);
        // }

        // if (frameCount == 100) {
        //     double fps = 1000.0 * frameCount / timeAccumulator;
        //     OLog::log(OLog::INFO, "FPS: " + std::to_string(fps));
        //     frameCount = 0;
        //     timeAccumulator = 0;
        // }
        // timeAccumulator += SDL_GetTicks() - frameStart;
        // frameCount++;
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

void Engine::Quit() { running = false; }
