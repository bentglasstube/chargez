#include "player.h"

void Player::draw(Graphics& graphics) const {
  const auto d = draw_point(pos_, 16);
  sprites_.draw(graphics, 0, d.x, d.y);

#ifndef NDEBUG
  const auto p = screen_coords(pos_);
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  graphics.draw_circle(p, kRadius, 0xd8ff00ff, false);
  graphics.draw_line(p, f, 0xd8ff00ff);
#endif
}

void Player::charge() { vel_ += vec2::polar(500.f, facing_); }

void Player::reset() {
  pos_ = {0.f, 0.f};
  vel_ = {0.f, 0.f};
  facing_ = 0.f;
}
