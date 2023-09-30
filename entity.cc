#include "entity.h"

void Entity::update(float t, vec2 force) {
  if (force.mag2() > 0.f) facing_ = force.angle();
  vel_ += force / mass_ * t;
  pos_ += vel_ * t;

  // very basic friction
  vel_ *= 0.95f;
}

void Entity::collision(Entity& other) {
  const float r = shape().radius + other.shape().radius;
  const vec2 d = other.pos_ - pos_;

  if (d.mag2() <= r * r) {
    const vec2 move = vec2::polar((r - d.mag()) / 2, d.angle());
    pos_ -= move;
    other.pos_ += move;

    const vec2 tan = d.perp().norm();
    const vec2 rel = other.vel_ - vel_;
    const float length = rel * tan;

    const vec2 vtan = tan * length;
    const vec2 vperp = rel - vtan;

    vel_ += vperp;
    other.vel_ -= vperp;
  }
}
