#pragma once

#include <random>

#include "entity.h"

class Pawn : public Entity {
 public:
  Pawn(vec2 pos, float facing, uint64_t seed)
      : Entity(pos, facing, 0.5f), rng_(seed) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;

 protected:
  static constexpr float kTurnInterval = 1.f;

  std::mt19937 rng_;
  float turn_timer_ = 0.f;
};

