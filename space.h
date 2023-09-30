#ifndef CHARGEZ_SPACE_H_
#define CHARGEZ_SPACE_H_

#include <random>
#include <vector>

#include "graphics.h"

class Space {
 public:
  Space(uint64_t seed);
  void update(float t);
  void draw(Graphics& graphics) const;

 private:
  struct Star {
    float x, y, z;
    uint32_t color;
  };

  static constexpr int kNumStars = 3000;
  static constexpr float kSpeed = 69.f * 4.f;
  static constexpr float kRatio = 420.f;
  static constexpr float kLightness = 0.90f;

  std::mt19937 rng_;
  std::vector<Star> stars_;

  const float width_, height_, depth_;
};

#endif  // CHARGEZ_SPACE_H_
