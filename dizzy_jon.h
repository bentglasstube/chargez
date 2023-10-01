#pragma once

#include <random>

#include "entity.h"

class DizzyJon : public Entity {
 public:
  DizzyJon(vec2 pos, float facing) : Entity(pos, facing, kMass) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;
  bool dizzying() const override { return true; }

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kMass = 0.5f;
  static constexpr float kRadius = 15.f;
  static constexpr float kTurnSpeed = M_PI / 2.f;
  static constexpr float kMoveSpeed = 100.f;

  float animation_timer_ = 0.f;

  int sprite() const { return tween(24, 39, animation_timer_); }
};
