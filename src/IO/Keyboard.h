/**
 * @file Keyboard.h
 * @author Owen McManus
 * @date 2025/4/12
 */

#pragma once
#include "../Utils/Keys.h"

#include <vector>

/**
 * @namespace OEngine::Keyboard
 * @brief Handles keyboard input management, including key events and state tracking.
 *
 * The `Keyboard` namespace contains functionality for connecting and disconnecting event listeners
 * for key press and release events. It also provides functions to query the state of the keyboard,
 * such as retrieving the list of currently pressed keys and checking whether a specific key is
 * pressed. This namespace is used to manage and track the state of keys across the game or
 * application.
 */
namespace OEngine::Keyboard {
/**
 * @brief Connects the keyboard to the event system by adding listeners for key events.
 */
void Connect();

/**
 * @brief Disconnects the keyboard from the event system by removing listeners and clearing the
 state.
 */
void Disconnect();

/**
 * @brief Retrieves a list of keys that are currently pressed.
 *
 * @return A vector containing the keys that are currently pressed.
 */
std::vector<Key::Keycode> GetPressed();

/**
 * @brief Checks if a specific key is currently pressed.
 *
 * @param key The `Keycode` of the key to check.
 *
 * @return `true` if the key is pressed, `false` otherwise.
 */
bool IsPressed(Key::Keycode key);
} // namespace OEngine::Keyboard
