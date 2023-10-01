#include "dizzy_jon.h"

void DizzyJon::update(float t, const Entity& player) {
  turn_toward(player, kTurnSpeed * t);
  Entity::update(t, vec2::polar(kMoveSpeed, facing_));
  animation_timer_ += t;
  if (animation_timer_ > 1.f) animation_timer_ -= 1.f;
}

void DizzyJon::draw(Graphics& graphics) const {
  const auto d = draw_point(pos_, 16);
  sprites_.draw(graphics, sprite(), d.x, d.y);

#ifndef NDEBUG
  const auto p = screen_coords(pos_);
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  graphics.draw_line(p, f, 0x000000ff);
#endif
}
