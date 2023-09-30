#include "pawn.h"

void Pawn::update(float t, const Entity&) {
  turn_timer_ -= t;
  if (turn_timer_ < 0) {
    turn_timer_ += std::uniform_real_distribution<float>(1.f, 2.5f)(rng_);
    vel_ += vec2::polar(50.f, facing_);
    target_dir_ = std::uniform_real_distribution<float>(
        facing_ - M_PI / 2.f, facing_ + M_PI / 2.f)(rng_);
  }
  Entity::update(t, vec2::polar(50.f, facing_));
  Entity::update(t);

  const float da = angle_diff(facing_, target_dir_);
  if (da < 0) {
    facing_ += std::max(da, -kTurnSpeed * t);
  } else if (da > 0) {
    facing_ += std::min(da, kTurnSpeed * t);
  }
}

void Pawn::draw(Graphics& graphics) const {
  const int px = graphics.width() / 2 + static_cast<int>(std::round(pos_.x));
  const int py = graphics.height() / 2 + static_cast<int>(std::round(pos_.y));
  const int ex = px + kRadius * std::cos(facing_);
  const int ey = py + kRadius * std::sin(facing_);
  const int tx = px + kRadius * 2 * std::cos(target_dir_);
  const int ty = py + kRadius * 2 * std::sin(target_dir_);

  graphics.draw_circle({px, py}, kRadius, 0xffd800ff, true);
  graphics.draw_line({px, py}, {ex, ey}, 0x000000ff);
  graphics.draw_line({px, py}, {tx, ty}, 0xff00d8ff);
}
