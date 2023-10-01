#include "kickler.h"

void Kickler::update(float t, const Entity& player) {
  if (state_ == State::Charging) {
    charge_timer_ -= t;
    turn_toward(player, kTurnSpeed * t);
    if (charge_timer_ < 0.f) {
      dash(kDashSpeed);
      state_ = State::Wandering;
    }
    Entity::update(t);
  } else if (state_ == State::Wandering) {
    if (dist2(wander_pos_) < kRadius * kRadius) wander_pos_ = random_pos();
    turn_toward(wander_pos_, kTurnSpeed * t);
    if (dist2(player) < kFollowDistance2) {
      state_ = State::Following;
    }
    Entity::update(t, vec2::polar(kWanderSpeed, facing_));
  } else if (state_ == State::Following) {
    turn_toward(player, kTurnSpeed * t);
    const float d2 = dist2(player);
    if (d2 < kChargeDistance2) {
      const float da = angle_diff(facing_, toward(player));
      if (std::abs(da) < kChargeAngle) {
        state_ = State::Charging;
        charge_timer_ = kChargeTime;
      }
    } else if (d2 > kFollowDistance2) {
      state_ = State::Wandering;
      wander_pos_ = random_pos();
    }
    Entity::update(t, vec2::polar(kFollowSpeed, facing_));
  }
}

void Kickler::draw(Graphics& graphics) const {
  const auto p = screen_coords(pos_);
  const uint32_t color = state_ == State::Wandering   ? 0x00ff00ff
                         : state_ == State::Following ? 0x0000ffff
                                                      : 0xff0000ff;

  graphics.draw_circle(p, kRadius, color, true);

#ifndef NDEBUG
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  graphics.draw_line(p, f, 0x000000ff);

  if (state_ == State::Wandering) {
    const auto t = screen_coords(wander_pos_);
    graphics.draw_line(p, t, 0xff00d8ff);
  }
#endif
}

vec2 Kickler::random_pos() {
  const float r = std::uniform_real_distribution<float>(0.f, 300.f)(rng_);
  const float a = std::uniform_real_distribution<float>(0.f, 2.f * M_PI)(rng_);
  return vec2::polar(r, a);
}
