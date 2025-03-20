#pragma once
#include <SDL2/SDL.h>

namespace OEngine {

struct SDL_Deleter {
    void operator()(SDL_Renderer* ptr) const {
        // OLog::log(OLog::DEBUG, "Clean Renderer");
        if (ptr)
            SDL_DestroyRenderer(ptr);
    }

    void operator()(SDL_Window* ptr) const {
        // OLog::log(OLog::DEBUG, "Clean Window");
        if (ptr)
            SDL_DestroyWindow(ptr);
    }

    void operator()(SDL_Texture* ptr) const {
        // OLog::log(OLog::DEBUG, "Clean Texture");
        if (ptr)
            SDL_DestroyTexture(ptr);
    }

    void operator()(SDL_Surface* ptr) const {
        // OLog::log(OLog::DEBUG, "Clean Surface");
        if (ptr)
            SDL_FreeSurface(ptr);
    }
};

} // namespace OEngine
