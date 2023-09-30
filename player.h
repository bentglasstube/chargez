#pragma once

#include "common.h"
#include "entity.h"
#include "graphics.h"

class Player : public Entity {
 public:
  Player() {}

  void draw(Graphics& graphics) const override;
  void charge();
  void reset();

  circle shape() const override { return {pos_, kRadius}; };

 private:
  static constexpr float kRadius = 15.f;
};
