cmake_minimum_required(VERSION 3.25)
project(OEngine VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# ─── Options ────────────────────────────────────────────────
option(OENGINE_FETCH_DEPS     "FetchContent third-party deps"       ON)
option(OENGINE_ENABLE_INSTALL "Generate install + export targets"   ON)
option(OENGINE_BUILD_TESTS    "Build OEngine unit tests"            OFF)
option(OENGINE_BUILD_EXAMPLES "Build example Game executable"       OFF)

# ─── Dependencies ────────────────────────────────────────────
if(OENGINE_FETCH_DEPS)
    include(FetchContent)

    # SDL3 Core
    set(SDL_STATIC  ON  CACHE BOOL "" FORCE)  # build static
    set(SDL_SHARED  ON  CACHE BOOL "" FORCE)  # build shared (needed by SDL3_image)
    set(SDL_INSTALL ON  CACHE BOOL "" FORCE)  # write a complete SDL3Config.cmake
    set(SDL3_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.2.10)
    FetchContent_MakeAvailable(SDL3)
    FetchContent_GetProperties(SDL3)
    set(SDL3_DIR "${SDL3_BINARY_DIR}" CACHE PATH "Path to SDL3" FORCE)
    list(PREPEND CMAKE_PREFIX_PATH "${SDL3_BINARY_DIR}")

    # SDL3_image
    set(SDL3IMAGE_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL3_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-3.2.4)

    # SDL3_ttf
    set(SDL3TTF_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL3_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-3.2.2)

    # OLog
    FetchContent_Declare(OLog
            GIT_REPOSITORY https://github.com/owen-mcmanus/OLog.git
            GIT_TAG v1.1.0)

    # glm
    FetchContent_Declare(glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1)

    # Abseil
    set(ABSL_ENABLE_INSTALL ON CACHE BOOL "" FORCE)
    FetchContent_Declare(abseil
            GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
            GIT_TAG 20240116.2)

    FetchContent_MakeAvailable(SDL3_image SDL3_ttf OLog glm abseil)
endif()

# ─── Library Target ──────────────────────────────────────────
add_library(OEngine STATIC
        # Core
        src/Core/Engine.cpp              src/Core/Engine.h
        src/Core/Scene.cpp               src/Core/Scene.h
        src/Core/SceneManager.cpp        src/Core/SceneManager.h
        src/Core/Window.cpp              src/Core/Window.h
        src/Core/Renderer.cpp            src/Core/Renderer.h
        src/Core/GameObject.cpp          src/Core/GameObject.h  src/Core/GameObject.tpp

        # Components
        src/Components/Sprite.cpp        src/Components/Sprite.h
        src/Components/Transform.cpp     src/Components/Transform.h
        src/Components/Collider.cpp      src/Components/Collider.h
        src/Components/PrimitiveSprite.cpp src/Components/PrimitiveSprite.h
        src/Components/Animation.cpp     src/Components/Animation.h

        # Events / IO / Utils
        src/Events/Event.cpp             src/Events/Event.h
        src/Events/EventManager.cpp      src/Events/EventManager.h
        src/IO/Keyboard.cpp              src/IO/Keyboard.h
        src/IO/Mouse.cpp                 src/IO/Mouse.h
        src/Utils/SDLDeleter.h           src/Utils/Keys.cpp
        src/Utils/Color.cpp              src/Utils/Color.h

        # UI / Asset / GameObjects
        src/UI/Objects/Button.cpp        src/UI/Objects/Button.h
        src/AssetManager/TextureCache.cpp
        src/AssetManager/TextureManager.cpp src/AssetManager/TextureManager.h
        src/AssetManager/FontManager.cpp src/AssetManager/FontManager.h
        src/GameObjects/Camera.cpp       src/GameObjects/Camera.h
        src/GameObjects/PrimitiveFactory.cpp src/GameObjects/PrimitiveFactory.h
)
add_library(OEngine::OEngine ALIAS OEngine)
target_compile_features(OEngine PUBLIC cxx_std_20)

target_include_directories(OEngine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/OEngine>
)

target_link_libraries(OEngine
        PUBLIC
        $<BUILD_INTERFACE:SDL3-static;SDL3_image-static;SDL3_ttf-static;OLog;glm::glm;absl::flat_hash_map>
)

# ─── Example Executable ──────────────────────────────────────
if(OENGINE_BUILD_EXAMPLES)
    add_executable(Game
            testGame/main.cpp
            testGame/TestScene.cpp
            testGame/Plane.cpp testGame/Plane.h)
    target_link_libraries(Game PRIVATE OEngine::OEngine)
endif()

# ─── Unit Tests ──────────────────────────────────────────────
if(OENGINE_BUILD_TESTS AND PROJECT_IS_TOP_LEVEL)
    enable_testing()
    add_subdirectory(tests)
endif()

# ─── Install / Export ────────────────────────────────────────
if(OENGINE_ENABLE_INSTALL)
    include(CMakePackageConfigHelpers)

    install(TARGETS OEngine
            EXPORT OEngineTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

    install(DIRECTORY src/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OEngine
            FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.tpp")

    install(EXPORT OEngineTargets
            FILE OEngineTargets.cmake
            NAMESPACE OEngine::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)

    configure_package_config_file(
            cmake/OEngineConfig.cmake.in
            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfig.cmake"
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion)

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfigVersion.cmake"
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)
endif()
