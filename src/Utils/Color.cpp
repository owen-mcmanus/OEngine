/**
 * @file Color.cpp
 * @author Owen McManus
 * @date 2025/5/4
 */

#include "Color.h"
#include <algorithm>
#include <cmath>

using namespace OEngine;

namespace {
inline float clamp(float v) { return std::clamp(v, 0.f, 1.f); }
} // namespace

Color Color::fromARGB32(uint32_t argb) {
    uint8_t a = (argb >> 24) & 0xFF;
    uint8_t r = (argb >> 16) & 0xFF;
    uint8_t g = (argb >> 8) & 0xFF;
    uint8_t b = argb & 0xFF;
    return fromBytes(r, g, b, a);
}

uint32_t Color::toARGB32() const {
    auto c = [](float f) { return static_cast<uint32_t>(clamp(f) * 255.f + 0.5f); };
    return (c(a) << 24) | (c(r) << 16) | (c(g) << 8) | c(b);
}

const Color Color::Black = Color(0.f, 0.f, 0.f, 1.f);
const Color Color::White = Color(1.f, 1.f, 1.f, 1.f);
const Color Color::Red = Color(1.f, 0.f, 0.f, 1.f);
const Color Color::Green = Color(0.f, 1.f, 0.f, 1.f);
const Color Color::Blue = Color(0.f, 0.f, 1.f, 1.f);
const Color Color::Transparent = Color(0.f, 0.f, 0.f, 0.f);

Color Color::operator+(const Color& c) const { return {r + c.r, g + c.g, b + c.b, a + c.a}; }

Color Color::operator-(const Color& c) const { return {r - c.r, g - c.g, b - c.b, a - c.a}; }

Color Color::operator*(float s) const { return {r * s, g * s, b * s, a * s}; }

Color Color::operator*(const Color& c) const { return {r * c.r, g * c.g, b * c.b, a * c.a}; }

Color& Color::operator+=(const Color& c) {
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

Color& Color::operator*=(float s) {
    r *= s;
    g *= s;
    b *= s;
    a *= s;
    return *this;
}

bool Color::operator==(const Color& c) const {
    constexpr float eps = 1e-6f;
    return std::fabs(r - c.r) < eps && std::fabs(g - c.g) < eps && std::fabs(b - c.b) < eps &&
           std::fabs(a - c.a) < eps;
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
    return os << "Color(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
}

Color Color::Lerp(const Color& a, const Color& b, float t) {
    return Color(
        a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t);
}