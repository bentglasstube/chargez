#pragma once

#include "entity.h"

class Pusher : public Entity {
 public:
  Pusher(vec2 pos, float facing) : Entity(pos, facing, kMass) {}

  void update(float t, const Entity&) override;
  void draw(Graphics& graphics) const override;

  circle shape() const override { return {pos_, kRadius}; }

 protected:
  static constexpr float kMass = 10.f;
  static constexpr float kRadius = 30.f;
  static constexpr float kTurnSpeed = M_PI / 8.f;
  static constexpr float kMoveSpeed = 1000.f;
};
