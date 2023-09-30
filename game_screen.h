#pragma once

#include <memory>
#include <random>
#include <vector>

#include "entity.h"
#include "player.h"
#include "screen.h"
#include "text.h"
#include "util.h"

class GameScreen : public Screen {
 public:
  GameScreen() : rng_(Util::random_seed()), text_("text.png") {}

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

  std::mt19937 rng_;
  State state_ = State::Playing;
  Player player_;
  std::vector<std::unique_ptr<Entity>> entities_;
  Text text_;
  int fade_timer_ = 0;
  float play_timer_ = 0.f;
  float spawn_timer_ = 0.f;

  void transition(State state);
  void spawn_enemy();

  bool out_of_bounds(const Entity& e) const;
};
