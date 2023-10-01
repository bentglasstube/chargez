#pragma once

#include <random>

#include "entity.h"

class Pawn : public Entity {
 public:
  Pawn(vec2 pos, float facing, uint64_t seed)
      : Entity(pos, facing, kMass), rng_(seed) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kMass = 0.2f;
  static constexpr float kRadius = 7.f;
  static constexpr float kTurnSpeed = M_PI / 4.f;
  static constexpr float kTurnAngle = kTurnSpeed * 2.f;
  static constexpr float kTurnTimerMin = 1.f;
  static constexpr float kTurnTimerMax = kTurnTimerMin * 2.5f;
  static constexpr float kMoveSpeed = 50.f;
  static constexpr float kDashSpeed = kMoveSpeed;

  std::mt19937 rng_;
  float turn_timer_ = 0.f;
  float target_dir_ = 0.f;
};

