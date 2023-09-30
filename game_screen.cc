#include "game_screen.h"

#include "common.h"

bool GameScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  const float t = elapsed / 1000.f;

  vec2 force;
  if (input.key_held(Input::Button::Up)) force.y += 1.f;
  if (input.key_held(Input::Button::Down)) force.y -= 1.f;
  if (input.key_held(Input::Button::Left)) force.x += 1.f;
  if (input.key_held(Input::Button::Right)) force.x -= 1.f;

  if (input.key_pressed(Input::Button::A)) player_.charge();

  if (force.mag() > 0.f) {
    player_.update(t, vec2::polar(1000.f, force.angle()));
  } else {
    player_.update(t);
  }

  return player_.pos().mag2() < 350 * 350;
}

void GameScreen::draw(Graphics& graphics) const {
  player_.draw(graphics);
  graphics.draw_circle({graphics.width() / 2, graphics.height() / 2}, 350,
                       0xffffffff, false);
}

Screen* GameScreen::next_screen() const { return nullptr; }
