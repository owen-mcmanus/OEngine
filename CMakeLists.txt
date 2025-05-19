# Top‑level CMakeLists.txt for the OEngine project
# Generates a static, installable package consumable with FetchContent or find_package(OEngine)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
project(OEngine VERSION 0.1.0 LANGUAGES CXX)

# ────────────────────────────────────────────────────────────────
# Global C++ setup
# ────────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Let parent projects prepend extra search paths for custom modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


# ────────────────────────────────────────────────────────────────
# Options
# ────────────────────────────────────────────────────────────────
option(OENGINE_BUILD_TESTS    "Build OEngine unit‑tests"          ON)
option(OENGINE_BUILD_EXAMPLES "Build example Game executable"     ON)
option(OENGINE_FETCH_DEPS     "FetchContent third‑party deps"     ON)

#project(OEngine)

# ────────────────────────────────────────────────────────────────
# Dependencies
# ────────────────────────────────────────────────────────────────
if(OENGINE_FETCH_DEPS)
    include(FetchContent)
    FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.2.10
    )
    set(SDL_STATIC ON)
    set(SDL_SHARED OFF)

    FetchContent_Declare(
            SDL_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-3.2.4
    )
    set(BUILD_SHARED_LIBS OFF)

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
    FetchContent_Declare(
            glm
            GIT_REPOSITORY	https://github.com/g-truc/glm.git
            GIT_TAG 	1.0.1
    )

    FetchContent_Declare(
            abseil
            GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
            GIT_TAG        20240116.2  # Use latest stable tag
    )
    set(ABSL_PROPAGATE_CXX_STD ON)
    set(ABSL_ENABLE_INSTALL OFF)
    set(ABSL_BUILD_TESTING OFF)

    FetchContent_MakeAvailable(SDL3 SDL_image SDL_ttf OLog glm abseil)
else()
    # Find pre‑installed packages instead of fetching
    find_package(SDL3       3 REQUIRED COMPONENTS SDL3-static)
    find_package(SDL3_image   REQUIRED COMPONENTS SDL3_image-static)
    find_package(SDL3_ttf     REQUIRED COMPONENTS SDL3_ttf-static)
    find_package(OLog         REQUIRED)
    find_package(glm          REQUIRED)
    find_package(absl         REQUIRED)
endif()

# ────────────────────────────────────────────────────────────────
# Engine sources
# ────────────────────────────────────────────────────────────────
set(OENGINE_SRC
        src/Core/Engine.cpp            src/Core/Engine.h
        src/Core/Scene.cpp             src/Core/Scene.h
        src/Core/SceneManager.cpp      src/Core/SceneManager.h
        src/Core/Window.cpp            src/Core/Window.h
        src/Core/Renderer.cpp          src/Core/Renderer.h
        src/Core/GameObject.cpp        src/Core/GameObject.h  src/Core/GameObject.tpp
        src/Components/Sprite.cpp      src/Components/Sprite.h
        src/Components/Transform.cpp   src/Components/Transform.h
        src/Components/Collider.cpp    src/Components/Collider.h
        src/Components/PrimitiveSprite.cpp src/Components/PrimitiveSprite.h
        src/Events/Event.cpp           src/Events/Event.h
        src/Events/EventManager.cpp    src/Events/EventManager.h
        src/IO/Keyboard.cpp            src/IO/Keyboard.h
        src/IO/Mouse.cpp               src/IO/Mouse.h
        src/Utils/SDLDeleter.h         src/Utils/Keys.cpp
        src/Utils/Color.cpp            src/Utils/Color.h
        src/UI/Objects/Button.cpp      src/UI/Objects/Button.h
        src/AssetManager/TextureCache.cpp
        src/AssetManager/TextureManager.cpp src/AssetManager/TextureManager.h
        src/GameObjects/Camera.cpp     src/GameObjects/Camera.h
        src/GameObjects/PrimitiveFactory.cpp src/GameObjects/PrimitiveFactory.h
        src/Components/Animation.cpp
        src/Components/Animation.h
        src/AssetManager/FontManager.cpp
        src/AssetManager/FontManager.h
)

# ────────────────────────────────────────────────────────────────
# Library target
# ────────────────────────────────────────────────────────────────
add_library(OEngine STATIC ${OENGINE_SRC})
add_library(OEngine::OEngine ALIAS OEngine)

# Public include paths (for both build‑tree & install‑tree)
# Consumers get <project>/src as the root include directory.
# Adjust if you eventually move headers to include/.
target_include_directories(OEngine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>)

# Link dependencies
target_link_libraries(OEngine
        PUBLIC
        SDL3::SDL3-static
        SDL3_image::SDL3_image-static
        SDL3_ttf::SDL3_ttf-static
        OLog
        glm::glm
        absl::flat_hash_map)

# ────────────────────────────────────────────────────────────────
# Example executable (optional)
# ────────────────────────────────────────────────────────────────
if(OENGINE_BUILD_EXAMPLES)
    add_executable(Game
            testGame/main.cpp
            testGame/TestScene.cpp
            testGame/Plane.cpp  testGame/Plane.h)
    target_link_libraries(Game PRIVATE OEngine::OEngine)
endif()

# ────────────────────────────────────────────────────────────────
# Unit‑tests (only when building stand‑alone)
# ────────────────────────────────────────────────────────────────
if(OENGINE_BUILD_TESTS AND PROJECT_IS_TOP_LEVEL)
    enable_testing()
    add_subdirectory(tests)
endif()

# ────────────────────────────────────────────────────────────────
# Collect third-party targets we built with FetchContent so they
# can be exported alongside OEngine.  This is required for a static
# library; otherwise install(EXPORT …) raises “not in any export set”.
# ────────────────────────────────────────────────────────────────
set(_OENGINE_EXPORT_DEPS)

if(OENGINE_FETCH_DEPS)  # only when we actually built them ourselves
    list(APPEND _OENGINE_EXPORT_DEPS
            SDL3-static
            SDL3_image-static
            SDL3_ttf-static
            glm
            absl_flat_hash_map
            OLog           # optional: add if your build tree defines this target
    )
endif()

# ────────────────────────────────────────────────────────────────
# Installation
# ────────────────────────────────────────────────────────────────
#include(GNUInstallDirs)
#include(CMakePackageConfigHelpers)
#
## Install the static library
#install(TARGETS OEngine ${_OENGINE_EXPORT_DEPS}
#        EXPORT  OEngineTargets
#        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#
## Install public headers (.h and .tpp)
#file(GLOB_RECURSE OENGINE_PUBLIC_HEADERS
#        CONFIGURE_DEPENDS
#        src/*.h src/*.tpp)
#install(FILES ${OENGINE_PUBLIC_HEADERS}
#        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OEngine)
#
## Export targets for find_package(OEngine)
#install(EXPORT OEngineTargets
#        FILE OEngineTargets.cmake
#        NAMESPACE OEngine::
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)
#
## Generate version file
#write_basic_package_version_file(
#        "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfigVersion.cmake"
#        VERSION ${PROJECT_VERSION}
#        COMPATIBILITY SameMajorVersion)
#
## Configure package config (template expected at cmake/OEngineConfig.cmake.in)
#configure_package_config_file(
#        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/OEngineConfig.cmake.in"
#        "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfig.cmake"
#        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)
#
#install(FILES
#        "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfig.cmake"
#        "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfigVersion.cmake"
#        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)


#include_directories(${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS} ${SDL3TTF_INCLUDE_DIR} ${OLOG_INCLUDE_DIR} ${GLM_INCLUDE_DIR} ${ABSEIL_INCLUDE_DIR})

#set(SOURCES
#        src/Core/Engine.cpp
#        src/Core/Scene.cpp
#        src/Core/SceneManager.cpp
#        src/Core/Window.cpp
#        src/Core/Renderer.cpp
#        src/Components/Sprite.cpp
#        src/Events/EventManager.cpp
#        src/AssetManager/TextureCache.cpp
#        src/AssetManager/TextureManager.cpp
#        src/AssetManager/TextureManager.h
#        src/Core/Engine.h
#        src/Core/Renderer.h
#        src/Core/Scene.h
#        src/Core/SceneManager.h
#        src/Components/Sprite.h
#        src/Core/Window.h
#        src/Events/EventManager.h
#        src/Utils/SDLDeleter.h
#        src/Events/Event.cpp
#        src/Events/Event.h
#        src/Utils/Keys.cpp
#        src/IO/Keyboard.cpp
#        src/IO/Keyboard.h
#        src/IO/Mouse.cpp
#        src/IO/Mouse.h
#        src/Core/GameObject.cpp
#        src/Core/GameObject.h
#        src/Core/GameObject.tpp
#        src/Components/Transform.cpp
#        src/Components/Transform.h
#        src/GameObjects/Camera.cpp
#        src/GameObjects/Camera.h
#        src/Components/Component.h
#        src/Components/PrimitiveSprite.cpp
#        src/Components/PrimitiveSprite.h
#        src/Utils/Color.cpp
#        src/Utils/Color.h
#        src/Components/Collider.cpp
#        src/Components/Collider.h
#        src/GameObjects/PrimitiveFactory.cpp
#        src/GameObjects/PrimitiveFactory.h
#)

#set(SOURCES_GAME
#        testGame/main.cpp
#        testGame/TestScene.cpp
#        testGame/Plane.cpp
#        testGame/Plane.h
#)

#add_library(OEngine STATIC ${SOURCES})
#target_link_libraries(OEngine PUBLIC SDL3::SDL3-static)
#target_link_libraries(OEngine PUBLIC SDL3_image::SDL3_image-static)
#target_link_libraries(OEngine PUBLIC SDL3_ttf::SDL3_ttf-static)
#target_link_libraries(OEngine PUBLIC OLog)
#target_link_libraries(OEngine PUBLIC glm::glm)
#target_link_libraries(OEngine PUBLIC absl::flat_hash_map)

#add_executable(Game ${SOURCES_GAME})
#target_link_libraries(Game PRIVATE OEngine)

#install(TARGETS OEngine DESTINATION /usr/local/lib)
#install(DIRECTORY include/ DESTINATION /usr/local/include)

#add_subdirectory(tests)