#include "hacker.h"

#include "config.h"

void Hacker::update(float t, const Entity& player) {
  turn_toward(-player.pos(), kTurnSpeed * t);
  Entity::update(t, kMoveSpeed);

  dash_timer_ -= t;
  if (dash_timer_ < 0) {
    dash(kDashSpeed);
    dash_timer_ += std::uniform_real_distribution<float>(kDashTimerMin,
                                                         kDashTimerMax)(rng_);
  }

  animation_timer_ += t;
  if (animation_timer_ > 0.5f) {
    animation_timer_ -= 0.5f;
    add_random_glitch();
  }

  for (auto& g : glitches_) {
    g.duration -= t;
  }
  std::erase_if(glitches_, [](const auto& g) { return g.duration <= 0.f; });
}

void Hacker::draw(Graphics& graphics) const {
  const auto d = draw_point(pos_, 16);
  sprites_.draw(graphics, sprite(), d.x, d.y);

#ifndef NDEBUG
  const auto p = screen_coords(pos_);
  const auto f = screen_coords(pos_ + vec2::polar(kRadius, facing_));
  graphics.draw_line(p, f, 0x000000ff);
#endif
}

void Hacker::draw_overlay(Graphics& graphics) const {
  for (const auto& g : glitches_) {
    graphics.draw_rect({g.x, g.y}, {g.x + g.w, g.y + g.h}, g.color, true);
  }
}

void Hacker::add_random_glitch() {
  const int width = kConfig.graphics.width;
  const int height = kConfig.graphics.height;

  std::uniform_real_distribution<float> color(0.f, 1.f);
  std::uniform_int_distribution<int> x(0, width);
  std::uniform_int_distribution<int> y(0, height);
  std::uniform_int_distribution<int> w(width / 2, width);
  std::uniform_int_distribution<int> h(4, 12);
  std::uniform_real_distribution<float> duration(0.1f, 0.3f);

  const Glitch g = {color(rng_) < 0.5 ? 0xffffffff : 0x000000ff,
                    x(rng_),
                    y(rng_),
                    w(rng_),
                    h(rng_),
                    duration(rng_)};
  glitches_.push_back(g);
}
