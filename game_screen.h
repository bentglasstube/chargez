#pragma once

#include "player.h"
#include "screen.h"
#include "text.h"

class GameScreen : public Screen {
 public:
  GameScreen() : text_("text.png") {}

  bool update(const Input&, Audio&, unsigned int) override;
  void draw(Graphics&) const override;
  Screen* next_screen() const override;

 private:
  enum class State {
    Playing,
    Paused,
    Dead,
    Exit,
  };

  State state_ = State::Playing;
  Player player_;
  Text text_;
  int fade_timer_ = 0;
  float play_timer_ = 0.f;
  int score_ = 0;

  void transition(State state);
};
