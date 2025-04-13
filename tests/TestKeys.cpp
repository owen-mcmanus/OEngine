#include "../src/Utils/Keys.h"
#include <SDL3/SDL.h>

#include <SDL3/SDL_keycode.h>
#include <gtest/gtest.h>

using namespace OEngine::Key;

TEST(KeyTest, ToCharUppercase_ReturnsUppercaseLetter) {
    EXPECT_EQ(ToCharUppercase(Keycode::A), 'A');
    EXPECT_EQ(ToCharUppercase(Keycode::N), 'N');
    EXPECT_EQ(ToCharUppercase(Keycode::Z), 'Z');
}

TEST(KeyTest, ToCharUppercase_ReturnsDigit) {
    EXPECT_EQ(ToCharUppercase(Keycode::ZERO), '0');
    EXPECT_EQ(ToCharUppercase(Keycode::FIVE), '5');
    EXPECT_EQ(ToCharUppercase(Keycode::NINE), '9');
}

TEST(KeyTest, ToCharUppercase_ReturnsZeroForInvalidInput) {
    // Invalid character (non A-Z, 0-9)
    EXPECT_EQ(ToCharUppercase(static_cast<Keycode>(123)), 0); // '{'
}

TEST(KeyTest, ToCharLowercase_ReturnsLowercaseLetter) {
    EXPECT_EQ(ToCharLowercase(Keycode::A), 'a');
    EXPECT_EQ(ToCharLowercase(Keycode::N), 'n');
    EXPECT_EQ(ToCharLowercase(Keycode::Z), 'z');
}

TEST(KeyTest, ToCharLowercase_ReturnsDigitUnchanged) {
    EXPECT_EQ(ToCharLowercase(Keycode::ZERO), '0');
    EXPECT_EQ(ToCharLowercase(Keycode::FIVE), '5');
    EXPECT_EQ(ToCharLowercase(Keycode::NINE), '9');
}

TEST(KeyTest, ToCharLowercase_ReturnsZeroForInvalidInput) {
    // Invalid character (non A-Z, 0-9)
    EXPECT_EQ(ToCharLowercase(static_cast<Keycode>(123)), 0); // '{'
}

TEST(SDLToKeyTest, DigitKeys) {
    EXPECT_EQ(SDLToKey(SDLK_0), Keycode::ZERO);
    EXPECT_EQ(SDLToKey(SDLK_1), Keycode::ONE);
    EXPECT_EQ(SDLToKey(SDLK_9), Keycode::NINE);
}

TEST(SDLToKeyTest, LetterKeys) {
    EXPECT_EQ(SDLToKey(SDLK_A), Keycode::A);
    EXPECT_EQ(SDLToKey(SDLK_M), Keycode::M);
    EXPECT_EQ(SDLToKey(SDLK_Z), Keycode::Z);
}

TEST(SDLToKeyTest, InvalidKeyReturnsDefault) {
    // EXPECT_EQ(SDLToKey('@'), Keycode::A); // before 'A'
    // EXPECT_EQ(SDLToKey('['), Keycode::A); // after 'Z'
    // EXPECT_EQ(SDLToKey(0), Keycode::A);   // null character
    // EXPECT_EQ(SDLToKey(200), Keycode::A); // out of range
}
