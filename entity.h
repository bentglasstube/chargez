#pragma once

#include "common.h"
#include "config.h"
#include "graphics.h"
#include "spritemap.h"

class Entity {
 public:
  Entity() : Entity({0.f, 0.f}) {}
  Entity(vec2 pos) : Entity(pos, 0.f, 1.f) {}
  Entity(vec2 pos, float facing, float mass)
      : sprites_("sprites.png", 8, 32, 32),
        pos_(pos),
        facing_(facing),
        mass_(mass) {}

  virtual ~Entity() {}

  void update(float t) { update(t, {0, 0}); }
  void update(float t, vec2 force);
  void update(float t, float force) { update(t, vec2::polar(force, facing_)); }
  virtual void update(float t, const Entity&) { update(t); }
  virtual void draw(Graphics& graphics) const = 0;
  virtual void draw_overlay(Graphics&) const {}
  virtual circle shape() const = 0;

  vec2 pos() const { return pos_; }
  vec2 vel() const { return vel_; }

  bool collision(Entity& other);
  virtual bool dizzying() const { return false; }

 protected:
  SpriteMap sprites_;
  vec2 pos_, vel_;
  float facing_ = 0;
  const float mass_ = 1.f;

  float toward(const Entity& e) const { return (e.pos_ - pos_).angle(); }
  float toward(vec2 p) const { return (p - pos_).angle(); }
  float dist2(const Entity& e) const { return pos_.dist2(e.pos_); }
  float dist2(vec2 p) const { return pos_.dist2(p); }

  void dash(float speed);
  void turn_toward(float target, float max);
  void turn_toward(const Entity& e, float max) { turn_toward(toward(e), max); }
  void turn_toward(vec2 p, float max) { turn_toward(toward(p), max); }

  static Graphics::Point screen_coords(vec2 p) {
    return {kConfig.graphics.width / 2 + static_cast<int>(std::round(p.x)),
            kConfig.graphics.height / 2 + static_cast<int>(std::round(p.y))};
  }

  static Graphics::Point draw_point(vec2 p, int offset) {
    const int px = static_cast<int>(std::round(p.x));
    const int py = static_cast<int>(std::round(p.y));
    return {kConfig.graphics.width / 2 + px - offset,
            kConfig.graphics.height / 2 + py - offset};
  }
};
