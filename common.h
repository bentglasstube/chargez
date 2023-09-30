#pragma once

#include <cmath>
#include <functional>

struct vec2 {
  float x = 0, y = 0;

  constexpr vec2 operator+(const vec2 o) const { return {x + o.x, y + o.y}; }
  constexpr vec2 operator-(const vec2 o) const { return {x - o.x, y - o.y}; }
  constexpr vec2 operator*(const float n) const { return {x * n, y * n}; }
  constexpr vec2 operator/(const float n) const { return {x / n, y / n}; }
  constexpr vec2 operator-() const { return {-x, -y}; }

  // dot product
  constexpr float operator*(const vec2 o) const { return x * o.x + y * o.y; }

  constexpr vec2& operator+=(const vec2 o) { return x += o.x, y += o.y, *this; }
  constexpr vec2& operator-=(const vec2 o) { return x -= o.x, y -= o.y, *this; }
  constexpr vec2& operator*=(const float n) { return x *= n, y *= n, *this; }
  constexpr vec2& operator/=(const float n) { return x /= n, y /= n, *this; }

  constexpr bool operator==(const vec2 o) const { return x == o.x && y == o.y; }
  constexpr bool operator!=(const vec2 o) const { return x != o.x || y != o.y; }

  constexpr float dist2(const vec2 o) const {
    const float dx = x - o.x;
    const float dy = y - o.y;
    return dx * dx + dy * dy;
  }

  float angle() const { return std::atan2(y, x); }
  float mag2() const { return x * x + y * y; }
  float mag() const { return std::sqrt(x * x + y * y); }

  static vec2 polar(float r, float theta) {
    return {r * std::cos(theta), r * std::sin(theta)};
  }
};
