set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(OEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIR})


set(SOURCES
        src/Core/Engine.cpp
        src/Core/Scene.cpp
        src/Core/SceneManager.cpp
        src/Core/Window.cpp
        src/Core/Renderer.cpp
        src/Core/Sprite.cpp
        src/AssetManager/TextureCache.cpp
        src/AssetManager/TextureManager.cpp
        src/Core/Engine.h
        src/Core/Renderer.h
        src/Core/Scene.h
        src/Core/SceneManager.h
        src/Core/Sprite.h
        src/Core/Window.h
)

set(SOURCES_GAME
        testGame/main.cpp
        testGame/TestScene.cpp
)

add_library(OEngine STATIC ${SOURCES})
target_link_libraries(OEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2TTF_LIBRARY} OLog)

add_executable(Game ${SOURCES_GAME})
target_link_libraries(Game OEngine)

#install(TARGETS OEngine DESTINATION /usr/local/lib)
#install(DIRECTORY include/ DESTINATION /usr/local/include)

add_subdirectory(tests)