/**
 * @file Delay.cpp
 * @author Owen McManus
 * @date 2025/5/18
 */
#include "Delay.h"

#include <SDL3/SDL_timer.h>

OEngine::Delay::Delay(uint32_t delay, std::function<void()> cb) : delay(delay), cb(cb) {
    startTime = SDL_GetTicks();
}

void OEngine::Delay::Update(double deltaTime) {
    if (complete)
        return;
    if (SDL_GetTicks() > startTime + delay) {
        cb();
        complete = true;
    }
}