#include "title_screen.h"

#include "game_screen.h"
#include "sprite.h"
#include "util.h"

TitleScreen::TitleScreen()
    : text_("text.png"),
      space_(Util::random_seed()),
      title_("title.png", 0, 0, 518, 177) {}

bool TitleScreen::update(const Input& input, Audio&, unsigned int elapsed) {
  space_.update(elapsed / 1000.f);

  if (lets_go) {
    fade_timer_ += elapsed;
    if (fade_timer_ > 1000) return false;
  } else {
    timer_ += elapsed;
    if (timer_ > 1000) timer_ -= 1000;
    if (input.key_pressed(Input::Button::Start)) {
      lets_go = true;
    }
  }
  title_timer_ += elapsed;

  return true;
}

namespace {
int tween(int a, int b, float value) {
  if (value <= 0.f) return a;
  if (value >= 1.f) return b;
  return a + static_cast<int>(std::round((b - a) * value));
}
}  // namespace

void TitleScreen::draw(Graphics& graphics) const {
  space_.draw(graphics);

  title_.draw(graphics, (graphics.width() - 518) / 2,
              tween(-200, 80, title_timer_ / 1000.f));

  if (lets_go) {
    uint32_t color = 0xffffff00 | tween(0, 0xff, fade_timer_ / 1000.f);
    graphics.draw_rect({0, 0}, {graphics.width(), graphics.height()}, color,
                       true);
  } else {
    if (timer_ < 500) {
      text_.draw(graphics, "Press start", graphics.width() / 2,
                 graphics.height() - 32, Text::Alignment::Center);
    }
  }
}

Screen* TitleScreen::next_screen() const { return new GameScreen(); }
