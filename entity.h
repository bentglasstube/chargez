#pragma once

#include "common.h"
#include "graphics.h"

class Entity {
 public:
  Entity() {}
  Entity(vec2 pos) : pos_(pos) {}
  Entity(vec2 pos, float facing, float mass)
      : pos_(pos), facing_(facing), mass_(mass) {}

  void update(float t) { update(t, {0, 0}); }
  void update(float t, vec2 force);
  virtual void update(float t, const Entity&) { update(t); }
  virtual void draw(Graphics& graphics) const = 0;

  vec2 pos() const { return pos_; }

 protected:
  vec2 pos_, vel_;
  float facing_ = 0;
  const float mass_ = 1.f;
};
