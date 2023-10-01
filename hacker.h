#pragma once

#include <random>
#include <vector>

#include "entity.h"

class Hacker : public Entity {
 public:
  Hacker(vec2 pos, float facing, uint64_t seed)
      : Entity(pos, facing, kMass), rng_(seed) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;
  void draw_overlay(Graphics& graphics) const override;

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kMass = 0.2f;
  static constexpr float kRadius = 15.f;
  static constexpr float kTurnSpeed = M_PI / 2.f;
  static constexpr float kMoveSpeed = 100.f;
  static constexpr float kDashSpeed = kMoveSpeed;
  static constexpr float kDashTimerMin = 0.5f;
  static constexpr float kDashTimerMax = 4.2f;

  struct Glitch {
    uint32_t color;
    int x, y, w, h;
    float duration;
  };

  std::mt19937 rng_;
  float dash_timer_ = 0.f;
  float animation_timer_ = 0.f;
  std::vector<Glitch> glitches_;

  void add_random_glitch();

  int sprite() const { return tween(16, 23, 2.f * animation_timer_); }
};
