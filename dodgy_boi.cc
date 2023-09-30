#include "dodgy_boi.h"

void DodgyBoi::update(float t, const Entity& player) {
  Entity::update(t, vec2::polar(10.f, facing_));
  if (cooldown_ > 0.f) cooldown_ -= t;

  if (player.vel().mag2() > kDodgeSpeed * kDodgeSpeed) {
    const vec2 d = pos() - player.pos();
    const float a = angle_diff(player.vel().angle(), d.angle());
    if (std::abs(a) <= kDodgeAngle && d.mag2() <= kDodgeDist * kDodgeDist) {
      // dodge
      vel_ += vec2::polar(250.f, d.perp().angle());
      cooldown_ = kDodgeCooldown;
    }
  }

  // turn toward the center if near the edge
  if (pos().mag2() > 300.f * 300.f) {
    facing_ = (vec2{0, 0} - pos()).angle();
  }
}

void DodgyBoi::draw(Graphics& graphics) const {
  const int px = graphics.width() / 2 + static_cast<int>(std::round(pos_.x));
  const int py = graphics.height() / 2 + static_cast<int>(std::round(pos_.y));
  graphics.draw_circle({px, py}, kRadius, 0x00d8ffff, true);
  if (cooldown_ <= 0.f)
    graphics.draw_circle({px, py}, kRadius, 0xffffffff, false);
}
