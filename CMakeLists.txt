set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(OEngine)

include(FetchContent)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.10
)
FetchContent_Declare(
        SDL_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-3.2.4
)
FetchContent_Declare(
        SDL_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG release-3.2.2
)
FetchContent_Declare(
        OLog
        GIT_REPOSITORY https://github.com/owen-mcmanus/OLog.git
        GIT_TAG v1.1.0
)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
FetchContent_MakeAvailable(SDL3)

set(BUILD_SHARED_LIBS OFF)
FetchContent_MakeAvailable(SDL_image)
FetchContent_MakeAvailable(SDL_ttf)

FetchContent_MakeAvailable(OLog)

include_directories(${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS} ${SDL3TTF_INCLUDE_DIR} ${OLOG_INCLUDE_DIR})


set(SOURCES
        src/Core/Engine.cpp
        src/Core/Scene.cpp
        src/Core/SceneManager.cpp
        src/Core/Window.cpp
        src/Core/Renderer.cpp
        src/Core/Sprite.cpp
        src/Events/EventManager.cpp
        src/AssetManager/TextureCache.cpp
        src/AssetManager/TextureManager.cpp
        src/AssetManager/TextureManager.h
        src/Core/Engine.h
        src/Core/Renderer.h
        src/Core/Scene.h
        src/Core/SceneManager.h
        src/Core/Sprite.h
        src/Core/Window.h
        src/Events/EventManager.h
        src/Utils/SDLDeleter.h
        src/Events/Event.cpp
        src/Events/Event.h
)

set(SOURCES_GAME
        testGame/main.cpp
        testGame/TestScene.cpp
        src/Utils/Keys.h
)

add_library(OEngine STATIC ${SOURCES})
target_link_libraries(OEngine PUBLIC SDL3::SDL3-static)
target_link_libraries(OEngine PUBLIC SDL3_image::SDL3_image-static)
target_link_libraries(OEngine PUBLIC SDL3_ttf::SDL3_ttf-static)
target_link_libraries(OEngine PUBLIC OLog)

add_executable(Game ${SOURCES_GAME})
target_link_libraries(Game PRIVATE OEngine)

#install(TARGETS OEngine DESTINATION /usr/local/lib)
#install(DIRECTORY include/ DESTINATION /usr/local/include)

add_subdirectory(tests)