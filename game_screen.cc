#include "game_screen.h"

#include <sstream>

#include "common.h"
#include "dizzy_jon.h"
#include "dodgy_boi.h"
#include "hacker.h"
#include "kickler.h"
#include "pawn.h"
#include "pusher.h"
#include "title_screen.h"

bool GameScreen::update(const Input& input, Audio& audio,
                        unsigned int elapsed) {
  if (state_ == State::Playing) {
    const float t = elapsed / 1000.f;

    play_timer_ += t;
    spawn_timer_ += t;
    dizzy_timer_ -= t;

    if (spawn_timer_ > 1.f) {
      spawn_timer_ -= 1.f;
      spawn_enemy();
    }

    vec2 force;
    if (input.key_held(Input::Button::Up)) force.y -= 1.f;
    if (input.key_held(Input::Button::Down)) force.y += 1.f;
    if (input.key_held(Input::Button::Left)) force.x -= 1.f;
    if (input.key_held(Input::Button::Right)) force.x += 1.f;

    if (input.key_pressed(Input::Button::A)) {
      player_.charge();
      audio.play_sample("dash.wav");
    }

    if (force.mag() > 0.f) {
      const float dir = dizzy_timer_ > 0.f ? -1000.f : 1000.f;
      player_.update(t, vec2::polar(dir, force.angle()));
    } else {
      player_.update(t);
    }

    for (auto&& e : entities_) {
      e->update(t, player_);
    }
    std::erase_if(entities_,
                  [this](const auto& e) { return out_of_bounds(*e); });

    if (out_of_bounds(player_)) {
      audio.play_sample("dead.wav");
      --lives_;
      if (lives_ == 0) audio.play_music("dropout.ogg", true);
      transition(State::Dead);
    }

    for (auto&& e : entities_) {
      if (e->collision(player_)) {
        if (e->dizzying()) {
          if (dizzy_timer_ <= 0.f) audio.play_sample("dizzy.wav");
          dizzy_timer_ = kDizzyDuration;
        } else {
          audio.play_random_sample("hit.wav", 9);
        }
      }
      for (auto&& f : entities_) {
        if (e != f) e->collision(*f);
      }
    }

    if (input.key_pressed(Input::Button::Start)) {
      audio.music_volume(3);
      transition(State::Paused);
    }
  } else if (state_ == State::Paused) {
    fade_timer_ += elapsed;
    if (input.key_pressed(Input::Button::Start)) {
      audio.music_volume(10);
      transition(State::Playing);
    }
  } else if (state_ == State::Dead) {
    fade_timer_ += elapsed;
    if (input.key_pressed(Input::Button::Start)) {
      if (lives_ == 0) {
        transition(State::Exit);
      } else {
        player_.reset();
        dizzy_timer_ = 0.f;
        transition(State::Playing);
      }
    }
  } else if (state_ == State::Exit) {
    fade_timer_ += elapsed;
    if (fade_timer_ > 1000) return false;
  }

  return true;
}

void GameScreen::draw(Graphics& graphics) const {
  for (const auto& e : entities_) {
    e->draw(graphics);
  }
  player_.draw(graphics);
  graphics.draw_circle({graphics.width() / 2, graphics.height() / 2}, 350,
                       0xffffffff, false);

  std::ostringstream time;
  const int seconds = static_cast<int>(std::floor(play_timer_));
  if (seconds >= 60) {
    time << std::to_string(seconds / 60) << ":";
    if ((seconds % 60) < 10) time << "0";
  }
  time << std::to_string(seconds % 60) << ".";
  const int centiseconds =
      static_cast<int>(std::floor((play_timer_ - seconds) * 100.f));
  if (centiseconds < 10) time << "0";
  time << std::to_string(centiseconds);
  text_.draw(graphics, time.str(), graphics.width(), 0, Text::Alignment::Right);

  for (int i = 0; i < lives_; ++i) {
    sprites_.draw(graphics, 13, 32 * i, 0);
  }

  for (const auto& e : entities_) {
    e->draw_overlay(graphics);
  }

  if (state_ == State::Paused) {
    uint32_t color = 0x00000000 | tween(0, 0x99, fade_timer_ / 200.f);
    graphics.draw_rect({0, 0}, {graphics.width(), graphics.height()}, color,
                       true);
    text_.draw(graphics, "Paused", graphics.width() / 2,
               graphics.height() / 2 - 8, Text::Alignment::Center);
  } else if (state_ == State::Dead) {
    uint32_t color = 0xff000000 | tween(0, 0x69, fade_timer_ / 500.f);
    graphics.draw_rect({0, 0}, {graphics.width(), graphics.height()}, color,
                       true);

    if (lives_ == 0) {
      text_.draw(graphics, "Game Over", graphics.width() / 2,
                 graphics.height() / 2 - 8, Text::Alignment::Center);
    }
  } else if (state_ == State::Exit) {
    uint32_t color = 0x00000000 | tween(0, 0xff, fade_timer_ / 1000.f);
    graphics.draw_rect({0, 0}, {graphics.width(), graphics.height()},
                       0xff000069, true);
    graphics.draw_rect({0, 0}, {graphics.width(), graphics.height()}, color,
                       true);
  }

  text_.draw(graphics, std::to_string(dizzy_timer_), 0, 64);
}

Screen* GameScreen::next_screen() const { return new TitleScreen(); }

void GameScreen::transition(State state) {
  fade_timer_ = 0;
  state_ = state;
}

void GameScreen::spawn_enemy() {
  std::uniform_real_distribution<float> angle(0.f, 2.f * M_PI);
  const float facing = angle(rng_);
  const float back = facing + static_cast<float>(M_PI);

  const float roll = std::uniform_real_distribution<float>(0.f, 1.f)(rng_);
  const vec2 pos = vec2::polar(340.f, facing);

  if (roll < 0.6f) {
    entities_.emplace_back(new Pawn{pos, back, rng_()});
  } else if (roll < 0.8f) {
    entities_.emplace_back(new DodgyBoi{pos, back, rng_()});
  } else if (roll < 0.9f) {
    entities_.emplace_back(new Kickler{pos, back, rng_()});
  } else if (roll < 0.95f) {
    entities_.emplace_back(new DizzyJon{pos, back});
  } else if (roll < 0.99f) {
    entities_.emplace_back(new Hacker{pos, back, rng_()});
  } else {
    entities_.emplace_back(new Pusher{pos, back});
  }
}

bool GameScreen::out_of_bounds(const Entity& e) const {
  const float r = 350 + e.shape().radius;
  return e.pos().mag2() >= r * r;
}
