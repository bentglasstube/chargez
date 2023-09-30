#include "space.h"

#include "config.h"

namespace {

uint32_t byte(float value) {
  if (value <= 0.f) return 0;
  if (value >= 1.f) return 0xff;
  return static_cast<uint32_t>(std::round(255 * value));
}

uint32_t fade_color(uint32_t color, float alpha) {
  return color & (0xffffff00 | byte(alpha));
}

uint32_t make_color(float r, float g, float b, float a = 1.f) {
  return byte(r) << 24 | byte(g) << 16 | byte(b) << 8 | byte(a);
}

uint32_t hsl(float hue, float sat, float light) {
  const float c = (1 - std::abs(2 * light - 1)) * sat;
  const float x = c * (1 - std::abs(std::fmod(hue / 60, 2) - 1));
  const float m = light - c / 2.f;

  if (hue < 60) {
    return make_color(c + m, x + m, m);
  } else if (hue < 120) {
    return make_color(x + m, c + m, m);
  } else if (hue < 180) {
    return make_color(m, c + m, x + m);
  } else if (hue < 240) {
    return make_color(m, x + m, c + m);
  } else if (hue < 300) {
    return make_color(x + m, m, c + m);
  } else {
    return make_color(x + m, m, x + m);
  }
}

}  // namespace

Space::Space(uint64_t seed)
    : rng_(seed),
      width_(kConfig.graphics.width),
      height_(kConfig.graphics.height),
      depth_((width_ + height_) / 2.f) {
  std::uniform_real_distribution<float> rx(-width_, width_);
  std::uniform_real_distribution<float> ry(-height_, height_);
  std::uniform_real_distribution<float> rz(0, depth_);
  std::uniform_real_distribution<float> hue(0.f, 360.f);

  stars_.reserve(kNumStars);
  for (size_t i = 0; i < kNumStars; ++i) {
    stars_.push_back(
        {rx(rng_), ry(rng_), rz(rng_), hsl(hue(rng_), 1.f, kLightness)});
  }
}

void Space::update(float t) {
  for (auto& star : stars_) {
    star.z -= kSpeed * t;
    if (star.z > depth_) {
      star.z -= depth_;
    } else if (star.z < 0) {
      star.z += depth_;
    }
  }
}

void Space::draw(Graphics& graphics) const {
  for (const auto& star : stars_) {
    const int sx = static_cast<int>(width_ / 2.f + (star.x / star.z) * kRatio);
    const int sy = static_cast<int>(height_ / 2.f + (star.y / star.z) * kRatio);
    graphics.draw_pixel({sx, sy},
                        fade_color(star.color, (1.f - star.z / depth_) * 2.f));
  }
}
