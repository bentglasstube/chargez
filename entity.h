#pragma once

#include "common.h"
#include "graphics.h"

class Entity {
 public:
  Entity() {}

  void update(float t) { update(t, {0, 0}); }
  void update(float t, vec2 force);
  virtual void draw(Graphics& graphics) const = 0;

  vec2 pos() const { return pos_; }

 protected:
  vec2 pos_, vel_;
  float facing_ = 0;
  const float mass_ = 1.f;
};
