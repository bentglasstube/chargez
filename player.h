#pragma once

#include "common.h"
#include "entity.h"
#include "graphics.h"

class Player : public Entity {
 public:
  Player() {}

  void draw(Graphics& graphics) const;
  void charge();
};
