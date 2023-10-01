#pragma once

#include "screen.h"
#include "space.h"
#include "sprite.h"
#include "spritemap.h"
#include "text.h"

class TitleScreen : public Screen {
 public:
  TitleScreen();

  bool update(const Input&, Audio&, unsigned int) override;
  void draw(Graphics&) const override;

  Screen* next_screen() const override;
  std::string get_music_track() const override { return "turnon.ogg"; }

 private:
  Text text_;
  Space space_;
  Sprite title_;
  SpriteMap sprites_;

  int timer_ = 0;
  int title_timer_ = 0;

  bool lets_go = false;
  int fade_timer_ = 0;

  int index = 0;
  int char_timer_ = 5000;

  int char_sprite() const;
  std::string char_name() const;
  std::string char_desc() const;
};
