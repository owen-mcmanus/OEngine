/**
 * @file SDLDeleter.h
 * @author Owen McManus
 * @date 2025/4/9
 */

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// #define LOG_DELETES

#ifdef LOG_DELETES
#include <olog.h>
#endif

namespace OEngine {

struct SDL_Deleter {
    void operator()(SDL_Renderer* ptr) const {
#ifdef LOG_DELETES
        OLog::log(OLog::DEBUG, "Clean Renderer");
#endif
        if (ptr)
            SDL_DestroyRenderer(ptr);
    }

    void operator()(SDL_Window* ptr) const {
#ifdef LOG_DELETES
        OLog::log(OLog::DEBUG, "Clean Window");
#endif
        if (ptr)
            SDL_DestroyWindow(ptr);
    }

    void operator()(SDL_Texture* ptr) const {
#ifdef LOG_DELETES
        OLog::log(OLog::DEBUG, "Clean Texture");
#endif
        if (ptr)
            SDL_DestroyTexture(ptr);
    }

    void operator()(SDL_Surface* ptr) const {
#ifdef LOG_DELETES
        OLog::log(OLog::DEBUG, "Clean Surface");
#endif
        if (ptr)
            SDL_DestroySurface(ptr);
    }

    void operator()(TTF_Font* ptr) const {
#ifdef LOG_DELETES
        OLog::log(OLog::DEBUG, "Clean Font");
#endif
        if (ptr)
            TTF_CloseFont(ptr);
    }
};

} // namespace OEngine

#undef LOG_DELETES