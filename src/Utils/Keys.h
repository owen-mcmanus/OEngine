/**
 * @file Keys.h
 * @author Owen McManus
 * @date 2025/4/12
 */

#pragma once
#include <cstdint>

/**
 * @namespace OEngine::Key
 * @brief Provides key-related functionality, including key codes and key state conversions.
 *
 * The `Key` namespace defines the `Keycode` enumeration, which represents various keys on the
 * keyboard, both printable and non-printable. It also includes utility functions to convert between
 * different key representations, such as converting SDL key codes to `Keycode` values and
 * converting `Keycode` values to their corresponding characters in uppercase or lowercase.
 *
 * This namespace is essential for handling key input in a cross-platform manner, ensuring that
 * key events are processed consistently regardless of the underlying system or input library.
 */
namespace OEngine::Key {

/**
 * @enum Keycode
 * @brief Represents the various keycodes for keyboard keys.
 *
 * This enum defines keycodes for both printable and non-printable characters, such as
 * letters, digits, and special keys (e.g., RETURN, ESCAPE, BACKSPACE).
 */
enum class Keycode {
    UNKNOWN = 0,
    RETURN = '\r',
    ESCAPE = '\x1B',
    BACKSPACE = '\b',
    TAB = '\t',
    SPACE = ' ',

    A = 'a',
    B = 'b',
    C = 'c',
    D = 'd',
    E = 'e',
    F = 'f',
    G = 'g',
    H = 'h',
    I = 'i',
    J = 'j',
    K = 'k',
    L = 'l',
    M = 'm',
    N = 'n',
    O = 'o',
    P = 'p',
    Q = 'q',
    R = 'r',
    S = 's',
    T = 't',
    U = 'u',
    V = 'v',
    W = 'w',
    X = 'x',
    Y = 'y',
    Z = 'z',

    ZERO = '0',
    ONE = '1',
    TWO = '2',
    THREE = '3',
    FOUR = '4',
    FIVE = '5',
    SIX = '6',
    SEVEN = '7',
    EIGHT = '8',
    NINE = '9',
};

/**
 * @brief Converts a `Keycode` to its uppercase character representation.
 *
 * This function converts a `Keycode` representing a letter to its uppercase character form.
 *
 * @param key The `Keycode` representing a key.
 * @return The uppercase character corresponding to the given `Keycode` or '\0' if the `Keycode`
 * does not map to a valid character.
 */
[[nodiscard]] char ToCharUppercase(Keycode key);

/**
 * @brief Converts a `Keycode` to its lowercase character representation.
 *
 * This function converts a `Keycode` representing a letter to its lowercase character form.
 *
 * @param key The `Keycode` representing a key.
 * @return The lowercase character corresponding to the given `Keycode` or '\0' if the `Keycode`
 * does not map to a valid character.
 */
[[nodiscard]] char ToCharLowercase(Keycode key);

/**
 * @brief Converts an SDL key value to a `Keycode`.
 *
 * This function maps an SDL key event (represented by a `uint32_t` SDL key value) to the
 * corresponding `Keycode`.
 *
 * @param sdlKey The SDL key value to be converted.
 * @return The corresponding `Keycode` representation of the SDL key.
 */
[[nodiscard]] Keycode SDLToKey(uint32_t sdlKey);
} // namespace OEngine::Key