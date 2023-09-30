#ifndef CHARGEZ_CONFIG_H_
#define CHARGEZ_CONFIG_H_

#include "game.h"

struct Config : public Game::Config {
  Config();
};
static const Config kConfig;

#endif  // CHARGEZ_CONFIG_H_
