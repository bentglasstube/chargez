#pragma once

#include <memory>
#include <random>
#include <vector>

#include "entity.h"
#include "player.h"
#include "screen.h"
#include "space.h"
#include "sprite.h"
#include "spritemap.h"
#include "text.h"
#include "util.h"

class GameScreen : public Screen {
 public:
  GameScreen()
      : rng_(Util::random_seed()),
        text_("text.png"),
        sprites_("sprites.png", 8, 32, 32),
        mask_("mask.png", 0, 0, 1280, 720),
        space_(rng_()) {}

  bool update(const Input&, Audio&, unsigned int) override;
  void draw(Graphics&) const override;
  Screen* next_screen() const override;
  std::string get_music_track() const override { return "tunein.ogg"; }

 private:
  enum class State {
    Playing,
    Paused,
    Dead,
    Exit,
  };

  static constexpr float kPlayerSpeed = 1000.f;
  static constexpr float kDizzyDuration = 2.5f;

  std::mt19937 rng_;
  State state_ = State::Playing;
  Player player_;
  std::vector<std::unique_ptr<Entity>> entities_;
  Text text_;
  SpriteMap sprites_;
  Sprite mask_;
  Space space_;
  int fade_timer_ = 0;
  float play_timer_ = 0.f;
  float spawn_timer_ = 0.f;
  float dizzy_timer_ = 0.f;
  int lives_ = 3;

  void transition(State state);
  void spawn_enemy();

  bool out_of_bounds(const Entity& e) const;
};
