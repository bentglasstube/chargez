#include "dodgy_boi.h"

void DodgyBoi::update(float t, const Entity& player) {
  Entity::update(t, vec2::polar(kMoveSpeed, facing_));
  if (cooldown_ > 0.f) cooldown_ -= t;

  if (player.vel().mag2() > kDodgeSpeed * kDodgeSpeed) {
    const vec2 d = pos() - player.pos();
    const float a = angle_diff(player.vel().angle(), d.angle());
    if (std::abs(a) <= kDodgeAngle && d.mag2() <= kDodgeDist2) {
      vel_ += vec2::polar(kDodgeSpeed, d.perp().angle());
      cooldown_ = kDodgeCooldown;
    }
  }

  if (dist2(wander_pos_) < kRadius * kRadius) wander_pos_ = random_pos();
  turn_toward(wander_pos_, kTurnSpeed * t);
}

void DodgyBoi::draw(Graphics& graphics) const {
  const auto p = screen_coords(pos_);
  graphics.draw_circle(p, kRadius, 0x00d8ffff, true);

#ifndef NDEBUG
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  graphics.draw_line(p, f, 0x000000ff);
  const auto t = screen_coords(wander_pos_);
  graphics.draw_line(p, t, 0xff00d8ff);
#endif
}

vec2 DodgyBoi::random_pos() {
  const float r = std::uniform_real_distribution<float>(250.f, 300.f)(rng_);
  const float a = std::uniform_real_distribution<float>(0.f, 2.f * M_PI)(rng_);
  return vec2::polar(r, a);
}
