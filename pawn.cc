#include "pawn.h"

void Pawn::update(float t, const Entity&) {
  turn_timer_ -= t;
  if (turn_timer_ < 0) {
    dash(kDashSpeed);
    turn_timer_ += std::uniform_real_distribution<float>(kTurnTimerMin,
                                                         kTurnTimerMax)(rng_);
    target_dir_ = std::uniform_real_distribution<float>(
        facing_ - kTurnAngle, facing_ + kTurnAngle)(rng_);
  }
  turn_toward(target_dir_, kTurnSpeed * t);
  Entity::update(t, vec2::polar(kMoveSpeed, facing_));
}

void Pawn::draw(Graphics& graphics) const {
  const auto d = draw_point(pos_, 16);
  sprites_.draw(graphics, 4, d.x, d.y);

#ifndef NDEBUG
  const auto p = screen_coords(pos_);
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  const auto t = screen_coords(pos_ + vec2::polar(kRadius * 2, target_dir_));
  graphics.draw_line(p, f, 0x000000ff);
  graphics.draw_line(p, t, 0xff00d8ff);
#endif
}
