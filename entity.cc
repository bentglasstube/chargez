#include "entity.h"

void Entity::update(float t, vec2 force) {
  if (force.mag2() > 0.f) facing_ = force.angle();
  vel_ += force / mass_ * t;
  pos_ += vel_ * t;

  // very basic friction
  // FIXME - friction effect depends on framerate
  vel_ *= 0.95f;
}

bool Entity::collision(Entity& other) {
  const float r = shape().radius + other.shape().radius;
  const vec2 d = other.pos_ - pos_;
  const float d2 = d.mag2();

  if (d2 <= r * r) {
    const vec2 move = vec2::polar(r - d.mag(), d.angle()) / 2.f;
    pos_ -= move;
    other.pos_ += move;

    const float total_mass = mass_ + other.mass_;
    const vec2 dv = other.vel_ - vel_;
    const vec2 col = d * (2 * (dv * d) / total_mass / d2);

    vel_ += col * other.mass_;
    other.vel_ -= col * mass_;

    return true;
  } else {
    return false;
  }
}

void Entity::dash(float speed) { vel_ += vec2::polar(speed, facing_); }
void Entity::turn_toward(float target, float max) {
  const float da = angle_diff(facing_, target);
  facing_ += da < 0 ? std::max(da, -max) : std::min(da, max);
}
