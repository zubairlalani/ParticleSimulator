#include "core/particle.h"

namespace idealgas{

void Particle::UpdatePosition() {
  position_ += velocity_;
}
void Particle::UpdateVelocity(bool x_or_y) {
  if(x_or_y)
    velocity_.x *= -1; // use correct formulas later
  else
    velocity_.y *= -1;
}

glm::vec2 Particle::GetPosition() {
  return position_;
}

glm::vec2 Particle::GetVelocity() {
  return velocity_;
}
void Particle::SetVelocity(glm::vec2 vel) {
  velocity_ = vel;
}
}

