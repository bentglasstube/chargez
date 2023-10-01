#include "pusher.h"

void Pusher::update(float t, const Entity& player) {
  turn_toward(player, kTurnSpeed * t);
  Entity::update(t, vec2::polar(kMoveSpeed, facing_));
}

void Pusher::draw(Graphics& graphics) const {
  const auto d = draw_point(pos_, 32);
  sprites_.draw(graphics, 6, d.x, d.y);
  sprites_.draw(graphics, 7, d.x + 32, d.y);
  sprites_.draw(graphics, 14, d.x, d.y + 32);
  sprites_.draw(graphics, 15, d.x + 32, d.y + 32);

#ifndef NDEBUG
  const auto p = screen_coords(pos_);
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  graphics.draw_line(p, f, 0x000000ff);
#endif
}
