cmake_minimum_required(VERSION 3.25)
project(OEngine VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# ─── Options ────────────────────────────────────────────────
option(OENGINE_FETCH_DEPS     "FetchContent third-party deps"       ON)
option(OENGINE_ENABLE_INSTALL "Generate install + export targets"   ON)
option(OENGINE_BUILD_TESTS    "Build OEngine unit tests"            OFF)
option(OENGINE_BUILD_EXAMPLES "Build example Game executable"       ON)

# ─── Dependencies ────────────────────────────────────────────
if(OENGINE_FETCH_DEPS)
    find_package(SDL3       CONFIG REQUIRED)
    find_package(SDL3_image CONFIG REQUIRED)
    find_package(SDL3_ttf   CONFIG REQUIRED)
    find_package(glm        CONFIG REQUIRED)
    find_package(absl       CONFIG REQUIRED)

    include(FetchContent)
    FetchContent_Declare(OLog
            GIT_REPOSITORY https://github.com/owen-mcmanus/OLog.git
            GIT_TAG v1.1.0)
    FetchContent_MakeAvailable(OLog)
#    find_package(olog       CONFIG REQUIRED)
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
        src/IO/Screen.cpp                 src/IO/Screen.h
        src/IO/TextInput.cpp                 src/IO/TextInput.h
        src/Utils/SDLDeleter.h           src/Utils/Keys.cpp
        src/Utils/Color.cpp              src/Utils/Color.h

        # UI / Asset / GameObjects
        src/UI/Objects/Button.cpp        src/UI/Objects/Button.h
        src/AssetManager/TextureCache.cpp
        src/AssetManager/TextureManager.cpp src/AssetManager/TextureManager.h
        src/AssetManager/FontManager.cpp src/AssetManager/FontManager.h
        src/GameObjects/Camera.cpp       src/GameObjects/Camera.h
        src/GameObjects/PrimitiveFactory.cpp src/GameObjects/PrimitiveFactory.h
        src/Components/Delay.cpp
        src/Components/Delay.h
        src/Utils/Viewport.cpp
        src/Utils/Viewport.h
        src/Components/MultiSprite.cpp
        src/Components/MultiSprite.h
        src/Components/PropertyChangeListener.cpp
        src/Components/PropertyChangeListener.h
)
add_library(OEngine::OEngine ALIAS OEngine)
target_compile_features(OEngine PUBLIC cxx_std_20)

target_include_directories(OEngine
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(OEngine
        PUBLIC SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf
        glm::glm
        absl::flat_hash_map
        OLog)

# ─── Example Executable ──────────────────────────────────────
#if(OENGINE_BUILD_EXAMPLES)
    add_executable(Game
            testGame/main.cpp
            testGame/TestScene.cpp
            testGame/Plane.cpp testGame/Plane.h)
    target_link_libraries(Game PRIVATE OEngine::OEngine)
#endif()

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
