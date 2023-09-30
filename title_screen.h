#pragma once

#include "screen.h"
#include "space.h"
#include "sprite.h"
#include "text.h"

class TitleScreen : public Screen {
 public:
  TitleScreen();

  bool update(const Input&, Audio&, unsigned int) override;
  void draw(Graphics&) const override;

  Screen* next_screen() const override;

 private:
  Text text_;
  Space space_;
  Sprite title_;

  int timer_ = 0;
  int title_timer_ = 0;

  bool lets_go = false;
  int fade_timer_ = 0;
};
