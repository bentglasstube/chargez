#include "title_screen.h"

#include "common.h"
#include "game_screen.h"
#include "sprite.h"
#include "util.h"

TitleScreen::TitleScreen()
    : text_("text.png"),
      space_(Util::random_seed()),
      title_("title.png", 0, 0, 518, 177),
      sprites_("sprites.png", 8, 32, 32) {}

bool TitleScreen::update(const Input& input, Audio& audio,
                         unsigned int elapsed) {
  space_.update(elapsed / 1000.f);

  if (lets_go) {
    fade_timer_ += elapsed;
    if (fade_timer_ > 1000) return false;
  } else {
    timer_ += elapsed;
    if (timer_ > 1380) timer_ -= 1380;
    if (input.key_pressed(Input::Button::Start)) {
      if (!lets_go) {
        lets_go = true;
        audio.play_sample("letsgo.wav");
      }
    }
  }
  title_timer_ += elapsed;

  char_timer_ += elapsed;
  if (char_timer_ > 10000) {
    index = (index + 1) % 8;
    char_timer_ = 0;
  }

  return true;
}

void TitleScreen::draw(Graphics& graphics) const {
  space_.draw(graphics);

  title_.draw(graphics, (graphics.width() - 518) / 2,
              tween(-200, 80, title_timer_ / 1000.f));

  if (lets_go) {
    uint32_t color = 0xffffff00 | tween(0, 0xff, fade_timer_ / 1000.f);
    graphics.draw_rect({0, 0}, {graphics.width(), graphics.height()}, color,
                       true);
  } else {
    if (timer_ < 690) {
      text_.draw(graphics, "Press start", graphics.width() / 2,
                 graphics.height() - 32, Text::Alignment::Center);
    }

    if (index > 0) {
      const int x = graphics.width() / 2;
      const int y = graphics.height() / 2;

      if (index == 6) {
        sprites_.draw(graphics, 6, x - 32, y - 32);
        sprites_.draw(graphics, 7, x, y - 32);
        sprites_.draw(graphics, 14, x - 32, y);
        sprites_.draw(graphics, 15, x, y);
      } else {
        sprites_.draw(graphics, char_sprite(), x - 16, y - 16);
      }
      text_.draw(graphics, char_name(), x, y + 40, Text::Alignment::Center);
      text_.draw(graphics, char_desc(), x, y + 64, Text::Alignment::Center);
    }
  }
}

Screen* TitleScreen::next_screen() const { return new GameScreen(); }

int TitleScreen::char_sprite() const {
  switch (index) {
    case 1:
      return 0;
    case 2:
      return 4;
    case 3:
      return 5;
    case 4:
      return 8;
    case 5:
      return 24;
    case 6:
      return 6;
    case 7:
      return 16;
    default:
      return 0;
  }
}

std::string TitleScreen::char_name() const {
  switch (index) {
    case 1:
      return "Player";
    case 2:
      return "Pawn";
    case 3:
      return "Dodgy Boi";
    case 4:
      return "Kickler";
    case 5:
      return "Dizzy Jon";
    case 6:
      return "Pusher";
    case 7:
      return "Hacker";
    default:
      return "";
  }
}

std::string TitleScreen::char_desc() const {
  switch (index) {
    case 1:
      return "This is you.  Don't get knocked outside of the ring.";
    case 2:
      return "They wander aimlessly.";
    case 3:
      return "They will dodge if you try to charge them.";
    case 4:
      return "They follow you and try to bump you when they're close.";
    case 5:
      return "They will disorient you if you touch them.";
    case 6:
      return "They are very strong but they are slow.";
    case 7:
      return "Their presence corrupts your view.";
    default:
      return "";
  }
}
