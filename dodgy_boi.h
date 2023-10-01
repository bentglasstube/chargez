#pragma once

#include <random>

#include "entity.h"

class DodgyBoi : public Entity {
 public:
  DodgyBoi(vec2 pos, float facing, uint64_t seed)
      : Entity(pos, facing, 0.05f), rng_(seed) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kRadius = 12.f;
  static constexpr float kMoveSpeed = 10.f;
  static constexpr float kTurnSpeed = 4.f * M_PI;
  static constexpr float kDodgeCooldown = 0.5f;
  static constexpr float kDodgeDist2 = square(50.f);
  static constexpr float kDodgeAngle = M_PI / 4.f;
  static constexpr float kDodgeSpeed = 500.f;

  std::mt19937 rng_;
  float cooldown_ = 0.f;
  vec2 wander_pos_ = {0.f, 0.f};

  vec2 random_pos();
};
