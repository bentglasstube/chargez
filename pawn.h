#pragma once

#include <random>

#include "entity.h"

class Pawn : public Entity {
 public:
  Pawn(vec2 pos, float facing, uint64_t seed)
      : Entity(pos, facing, 0.2f), rng_(seed) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kRadius = 7.f;
  static constexpr float kTurnSpeed = M_PI / 4.f;

  std::mt19937 rng_;
  float turn_timer_ = 0.f;
  float target_dir_ = 0.f;
};

