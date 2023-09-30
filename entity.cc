#include "entity.h"

void Entity::update(float t, vec2 force) {
  if (force.mag2() > 0.f) facing_ = force.angle();
  vel_ += force / mass_ * t;
  pos_ += vel_ * t;

  // very basic friction
  vel_ *= 0.95f;
}
