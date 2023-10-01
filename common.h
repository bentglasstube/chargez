#pragma once

#include <cmath>

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

  constexpr vec2 norm() const {
    const float m = mag();
    return {x / m, y / m};
  }

  constexpr float angle() const { return std::atan2(y, x); }
  constexpr float mag2() const { return x * x + y * y; }
  constexpr float mag() const { return std::sqrt(x * x + y * y); }
  constexpr vec2 perp() const { return {-y, x}; }

  static vec2 polar(float r, float theta) {
    return {r * std::cos(theta), r * std::sin(theta)};
  }
};

inline int tween(int a, int b, float v) {
  if (v <= 0.f) return a;
  if (v >= 1.f) return b;
  return a + static_cast<int>(std::round((b - a) * v));
}

struct circle {
  vec2 pos;
  float radius;

  constexpr bool intersect(const circle& other) const {
    const float r = radius + other.radius;
    return pos.dist2(other.pos) <= r * r;
  }
};

vec2 closest_point_on_line(vec2 a, vec2 b, vec2 p);

constexpr float angle_diff(float v, float w) {
  const float d = w - v;
  if (d > M_PI) return d - 2.f * M_PI;
  if (d < -M_PI) return d + 2.f * M_PI;
  return d;
}

constexpr float square(float n) { return n * n; }
