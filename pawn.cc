#include "pawn.h"

void Pawn::update(float t, const Entity&) {
  turn_timer_ -= t;
  if (turn_timer_ < 0) {
    turn_timer_ += std::uniform_real_distribution<float>(1.f, 2.5f)(rng_);
    vel_ += vec2::polar(100.f, facing_);
    facing_ = std::uniform_real_distribution<float>(facing_ - 0.5f,
                                                    facing_ + 0.5f)(rng_);
  }
  Entity::update(t, vec2::polar(100.f, facing_));
  Entity::update(t);
}

void Pawn::draw(Graphics& graphics) const {
  const int px = graphics.width() / 2 - static_cast<int>(std::round(pos_.x));
  const int py = graphics.height() / 2 - static_cast<int>(std::round(pos_.y));
  const int ex = px - 7.f * std::cos(facing_);
  const int ey = py - 7.f * std::sin(facing_);
  graphics.draw_circle({px, py}, 7.f, 0xffd800ff, true);
  graphics.draw_line({px, py}, {ex, ey}, 0x000f00ff);
}
