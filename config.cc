#include "config.h"

Config::Config() : Game::Config() {
  graphics.title = "Chargez";
  graphics.width = 1280;
  graphics.height = 720;
  graphics.scale = 1;
  graphics.intscale = false;
  graphics.fullscreen = true;
}
