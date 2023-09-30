#include "common.h"

vec2 closest_point_on_line(vec2 a, vec2 b, vec2 p) {
  const float dy = b.y - a.y;
  const float dx = a.x - b.x;
  const float c1 = dx * a.x + dy * a.y;
  const float c2 = dx * p.y - dy * p.x;
  const float det = dx * dx + dy * dy;
  if (det == 0.f) {
    return {0.f, 0.f};
  } else {
    return {(dx * c1 - dy * c2) / det, (dx * c2 + dy * c1) / det};
  }
}
