#pragma once

#include <random>

#include "entity.h"

class Kickler : public Entity {
 public:
  Kickler(vec2 pos, float facing, uint64_t seed)
      : Entity(pos, facing, kMass), rng_(seed), wander_pos_(random_pos()) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kMass = 2.f;
  static constexpr float kRadius = 15.f;
  static constexpr float kTurnSpeed = M_PI / 4.f;
  static constexpr float kFollowDistance2 = square(200.f);
  static constexpr float kChargeDistance2 = square(kRadius * 5.f);
  static constexpr float kChargeAngle = M_PI / 16.f;
  static constexpr float kWanderSpeed = 100.f;
  static constexpr float kFollowSpeed = kWanderSpeed * 2.f;
  static constexpr float kDashSpeed = kWanderSpeed * 5.f;
  static constexpr float kChargeTime = 0.5f;

  enum class State {
    Wandering,
    Following,
    Charging,
  };

  std::mt19937 rng_;
  float target_dir_ = 0.f;
  float charge_timer_ = 0.f;
  vec2 wander_pos_ = {0.f, 0.f};
  State state_ = State::Wandering;

  vec2 random_pos();
};
