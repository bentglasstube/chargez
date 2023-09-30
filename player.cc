#include "player.h"

void Player::draw(Graphics& graphics) const {
  const int px = graphics.width() / 2 + static_cast<int>(std::round(pos_.x));
  const int py = graphics.height() / 2 + static_cast<int>(std::round(pos_.y));
  const int ex = px + kRadius * std::cos(facing_);
  const int ey = py + kRadius * std::sin(facing_);
  graphics.draw_circle({px, py}, kRadius, 0xd8ff00ff, false);
  graphics.draw_line({px, py}, {ex, ey}, 0xd8ff00ff);
}

void Player::charge() { vel_ += vec2::polar(500.f, facing_); }
