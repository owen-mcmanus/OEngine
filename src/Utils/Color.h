/**
 * @file Color.h
 * @author Owen McManus
 * @date 2025/5/4
 */

#pragma once

#include <cstdint>
#include <ostream>

namespace OEngine {
class Color {
  public:
    static const Color Black, White, Red, Green, Blue, Transparent;
    static Color Lerp(const Color& a, const Color& b, float t);
    static Color fromARGB32(uint32_t argb);

    static constexpr Color
    fromBytes(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) {
        return Color(red / 255.f, green / 255.f, blue / 255.f, alpha / 255.f);
    }

    constexpr Color() : r(0.f), g(0.f), b(0.f), a(1.f) {}

    constexpr Color(float red, float green, float blue, float alpha = 1.f)
        : r(red), g(green), b(blue), a(alpha) {}

    uint32_t toARGB32() const;

    Color operator+(const Color& c) const;
    Color operator-(const Color& c) const;
    Color operator*(float s) const;
    Color operator*(const Color& c) const;
    Color& operator+=(const Color& c);
    Color& operator*=(float s);

    bool operator==(const Color& c) const;

    bool operator!=(const Color& c) const { return !(*this == c); }

    friend std::ostream& operator<<(std::ostream& os, const Color& c);

    float r, g, b, a;
};

inline std::ostream& operator<<(std::ostream& s, const Color& c) {
    s << c.r << ", " << c.g << ", " << c.b << ", " << c.a;
    return s;
}

} // namespace OEngine
