#pragma once

#include "player.h"
#include "screen.h"

class GameScreen : public Screen {
 public:
  GameScreen() {}

  bool update(const Input&, Audio&, unsigned int) override;
  void draw(Graphics&) const override;
  Screen* next_screen() const override;

 private:
  Player player_;
};
