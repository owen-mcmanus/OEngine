cmake_minimum_required(VERSION 3.25)
project(OEngine VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)

# ───── options ──────────────────────────────────────────────────────────
option(OENGINE_FETCH_DEPS     "FetchContent third-party deps"      ON)
option(OENGINE_ENABLE_INSTALL "Generate install + export targets"  ON)

# ───── dependencies (build tree) ───────────────────────────────────────
if(OENGINE_FETCH_DEPS)
    include(FetchContent)

    # SDL3 ──────────────────────────────────────────────────────────────
    set(SDL_STATIC  ON  CACHE BOOL "" FORCE)
    set(SDL_SHARED  OFF CACHE BOOL "" FORCE)
    set(SDL3_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG        release-3.2.10)
    FetchContent_MakeAvailable(SDL3)
    # --- make sure the alias exists (needed if SDL_SHARED=OFF) --------------
    if (TARGET SDL3-static AND NOT TARGET SDL3::SDL3)
        add_library(SDL3::SDL3 ALIAS SDL3-static)
    endif()

    # expose build-tree SDL3 to siblings
    FetchContent_GetProperties(SDL3)
    set(SDL3_DIR "${SDL3_BINARY_DIR}" CACHE PATH "" FORCE)
    list(PREPEND CMAKE_PREFIX_PATH "${SDL3_BINARY_DIR}")

    # SDL3_image ───────────────────────────────────────────────────────
    set(SDL3IMAGE_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL3_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG        release-3.2.4)

    # SDL3_ttf ─────────────────────────────────────────────────────────
    set(SDL3TTF_DISABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(SDL3_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG        release-3.2.2)

    # OLog ─────────────────────────────────────────────────────────────
    FetchContent_Declare(OLog
            GIT_REPOSITORY https://github.com/owen-mcmanus/OLog.git
            GIT_TAG        v1.1.0)

    # glm ──────────────────────────────────────────────────────────────
    FetchContent_Declare(glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG        1.0.1)

    # Abseil ───────────────────────────────────────────────────────────
    set(ABSL_ENABLE_INSTALL ON CACHE BOOL "" FORCE)
    FetchContent_Declare(abseil
            GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
            GIT_TAG        20240116.2)

    FetchContent_MakeAvailable(SDL3_image SDL3_ttf OLog glm abseil)
endif()

# ───── library ─────────────────────────────────────────────────────────
add_library(OEngine STATIC
         #core
                src/Core/Engine.cpp            src/Core/Engine.h
                src/Core/Scene.cpp             src/Core/Scene.h
                src/Core/SceneManager.cpp      src/Core/SceneManager.h
                src/Core/Window.cpp            src/Core/Window.h
                src/Core/Renderer.cpp          src/Core/Renderer.h
                src/Core/GameObject.cpp        src/Core/GameObject.h  src/Core/GameObject.tpp
                # components
                src/Components/Sprite.cpp      src/Components/Sprite.h
                src/Components/Transform.cpp   src/Components/Transform.h
                src/Components/Collider.cpp    src/Components/Collider.h
                src/Components/PrimitiveSprite.cpp src/Components/PrimitiveSprite.h
                src/Components/Animation.cpp   src/Components/Animation.h
                # events / IO / utils / asset managers
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
                src/AssetManager/FontManager.cpp src/AssetManager/FontManager.h
)
add_library(OEngine::OEngine ALIAS OEngine)

target_compile_features(OEngine PUBLIC cxx_std_20)

target_include_directories(OEngine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# All build-tree deps are PRIVATE, wrapped so they **never** leak to install
target_link_libraries(OEngine
        PUBLIC                                                # headers need them
        $<BUILD_INTERFACE:SDL3-static;SDL3_image-static;
        SDL3_ttf-static;OLog;
        glm::glm;absl::flat_hash_map>
)

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


# ───── install / export ────────────────────────────────────────────────
if(OENGINE_ENABLE_INSTALL)
    include(CMakePackageConfigHelpers)

    install(TARGETS OEngine
            EXPORT  OEngineTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

    install(DIRECTORY src/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OEngine
            FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.tpp")

    install(EXPORT OEngineTargets
            FILE      OEngineTargets.cmake
            NAMESPACE OEngine::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)

    # ---- package config ----
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














## Top‑level CMakeLists.txt for the OEngine project
## Generates a static, installable package consumable with FetchContent or find_package(OEngine)
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#
#cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
#project(OEngine VERSION 0.1.0 LANGUAGES CXX)
#
## ────────────────────────────────────────────────────────────────
## Global C++ setup
## ────────────────────────────────────────────────────────────────
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#
## Let parent projects prepend extra search paths for custom modules
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#
#
## ────────────────────────────────────────────────────────────────
## Options
## ────────────────────────────────────────────────────────────────
#option(OENGINE_BUILD_TESTS    "Build OEngine unit‑tests"          ON)
#option(OENGINE_BUILD_EXAMPLES "Build example Game executable"     ON)
#option(OENGINE_FETCH_DEPS     "FetchContent third‑party deps"     ON)
## Only generate install/packaging targets when building OEngine stand‑alone
#option(OENGINE_ENABLE_INSTALL "Enable install rules (turn OFF when pulled via FetchContent)" OFF)
#
## ────────────────────────────────────────────────────────────────
## Dependencies
## ────────────────────────────────────────────────────────────────
#if(OENGINE_FETCH_DEPS)
#    include(FetchContent)
#    FetchContent_Declare(
#            SDL3
#            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
#            GIT_TAG release-3.2.10
#    )
#    set(SDL_STATIC ON)
#    set(SDL_SHARED OFF)
#
#    FetchContent_Declare(
#            SDL_image
#            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
#            GIT_TAG release-3.2.4
#    )
#    set(BUILD_SHARED_LIBS OFF)
#
#    FetchContent_Declare(
#            SDL_ttf
#            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
#            GIT_TAG release-3.2.2
#    )
#    FetchContent_Declare(
#            OLog
#            GIT_REPOSITORY https://github.com/owen-mcmanus/OLog.git
#            GIT_TAG v1.1.0
#    )
#    FetchContent_Declare(
#            glm
#            GIT_REPOSITORY	https://github.com/g-truc/glm.git
#            GIT_TAG 	1.0.1
#    )
#
#    FetchContent_Declare(
#            abseil
#            GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
#            GIT_TAG        20240116.2  # Use latest stable tag
#    )
#    set(ABSL_PROPAGATE_CXX_STD ON)
#    set(ABSL_ENABLE_INSTALL OFF)
#    set(ABSL_BUILD_TESTING OFF)
#
#    if(OENGINE_ENABLE_INSTALL)
#        set(SDL3_INSTALL         ON CACHE BOOL "" FORCE)
#        set(SDL3IMAGE_INSTALL    ON CACHE BOOL "" FORCE)
#        set(SDL3TTF_INSTALL      ON CACHE BOOL "" FORCE)
#        set(ABSL_ENABLE_INSTALL  ON CACHE BOOL "" FORCE)
#    endif()
#
#    FetchContent_MakeAvailable(SDL3 SDL_image SDL_ttf OLog glm abseil)
#else()
#    # Find pre‑installed packages instead of fetching
#    find_package(SDL3         REQUIRED COMPONENTS SDL3-static)
#    find_package(SDL3_image   REQUIRED COMPONENTS SDL3_image-static)
#    find_package(SDL3_ttf     REQUIRED COMPONENTS SDL3_ttf-static)
#    find_package(OLog         REQUIRED)
#    find_package(glm          REQUIRED)
#    find_package(absl         REQUIRED)
#endif()
#
## ────────────────────────────────────────────────────────────────
## Engine sources
## ────────────────────────────────────────────────────────────────
#set(OENGINE_SRC
#        # core
#        src/Core/Engine.cpp            src/Core/Engine.h
#        src/Core/Scene.cpp             src/Core/Scene.h
#        src/Core/SceneManager.cpp      src/Core/SceneManager.h
#        src/Core/Window.cpp            src/Core/Window.h
#        src/Core/Renderer.cpp          src/Core/Renderer.h
#        src/Core/GameObject.cpp        src/Core/GameObject.h  src/Core/GameObject.tpp
#        # components
#        src/Components/Sprite.cpp      src/Components/Sprite.h
#        src/Components/Transform.cpp   src/Components/Transform.h
#        src/Components/Collider.cpp    src/Components/Collider.h
#        src/Components/PrimitiveSprite.cpp src/Components/PrimitiveSprite.h
#        src/Components/Animation.cpp   src/Components/Animation.h
#        # events / IO / utils / asset managers
#        src/Events/Event.cpp           src/Events/Event.h
#        src/Events/EventManager.cpp    src/Events/EventManager.h
#        src/IO/Keyboard.cpp            src/IO/Keyboard.h
#        src/IO/Mouse.cpp               src/IO/Mouse.h
#        src/Utils/SDLDeleter.h         src/Utils/Keys.cpp
#        src/Utils/Color.cpp            src/Utils/Color.h
#        src/UI/Objects/Button.cpp      src/UI/Objects/Button.h
#        src/AssetManager/TextureCache.cpp
#        src/AssetManager/TextureManager.cpp src/AssetManager/TextureManager.h
#        src/GameObjects/Camera.cpp     src/GameObjects/Camera.h
#        src/GameObjects/PrimitiveFactory.cpp src/GameObjects/PrimitiveFactory.h
#        src/AssetManager/FontManager.cpp src/AssetManager/FontManager.h
#)
#
## ────────────────────────────────────────────────────────────────
## Library target
## ────────────────────────────────────────────────────────────────
#add_library(OEngine STATIC ${OENGINE_SRC})
#add_library(OEngine::OEngine ALIAS OEngine)
#
#target_include_directories(OEngine
#        PUBLIC
#        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
#        $<INSTALL_INTERFACE:include>)
#
##target_link_libraries(OEngine
##        PRIVATE
##        SDL3::SDL3-static
##        SDL3_image::SDL3_image-static
##        SDL3_ttf::SDL3_ttf-static
##        OLog
##        glm::glm
##        absl::flat_hash_map)
#
#target_link_libraries(OEngine
#        PUBLIC
#        # ---- use these while the engine is *in* the build tree ----
#        $<BUILD_INTERFACE:SDL3-static;SDL3_image-static;SDL3_ttf-static;
#        OLog;glm::glm;absl::flat_hash_map>
#
#        # ---- use these after the engine is *installed* ----
#        $<INSTALL_INTERFACE:SDL3::SDL3;SDL3_image::SDL3_image;
#        SDL3_ttf::SDL3_ttf;OLog::OLog;
#        glm::glm;absl::flat_hash_map>
#)
#
#
## ────────────────────────────────────────────────────────────────
## Example executable (optional)
## ────────────────────────────────────────────────────────────────
#if(OENGINE_BUILD_EXAMPLES)
#    add_executable(Game
#            testGame/main.cpp
#            testGame/TestScene.cpp
#            testGame/Plane.cpp  testGame/Plane.h)
#    target_link_libraries(Game PRIVATE OEngine::OEngine)
#endif()
#
## ────────────────────────────────────────────────────────────────
## Unit‑tests (only when building stand‑alone)
## ────────────────────────────────────────────────────────────────
#if(OENGINE_BUILD_TESTS AND PROJECT_IS_TOP_LEVEL)
#    enable_testing()
#    add_subdirectory(tests)
#endif()
#
## ────────────────────────────────────────────────────────────────
## Install / packaging – only when explicitly enabled
## ────────────────────────────────────────────────────────────────
#if(OENGINE_ENABLE_INSTALL)
#
#    # 1. Library
#    install(TARGETS OEngine
#            EXPORT  OEngineTargets
#            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
#
#    # 2. Headers
#    install(DIRECTORY src/
#            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/OEngine
#            FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp" PATTERN "*.tpp")
#
#    # 3. Export target file
#    install(EXPORT OEngineTargets
#            FILE       OEngineTargets.cmake
#            NAMESPACE  OEngine::
#            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OEngine)
#
#    # 4. Package Config + Version files
#    configure_package_config_file(
#            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/OEngineConfig.cmake.in"
#            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfig.cmake"
#            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OEngine")
#
#    write_basic_package_version_file(
#            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfigVersion.cmake"
#            VERSION     ${PROJECT_VERSION}
#            COMPATIBILITY SameMajorVersion)
#
#    install(FILES
#            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfig.cmake"
#            "${CMAKE_CURRENT_BINARY_DIR}/OEngineConfigVersion.cmake"
#            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OEngine")
#
#    # 5. Export from build‑tree (optional)
#    export(EXPORT OEngineTargets
#            FILE     "${CMAKE_CURRENT_BINARY_DIR}/OEngineTargets.cmake"
#            NAMESPACE OEngine::)
#endif()

















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