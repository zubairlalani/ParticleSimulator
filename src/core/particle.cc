#include "core/particle.h"

namespace idealgas{

void Particle::UpdatePosition() {
  position += velocity;
}
void Particle::UpdateVelocity() {
  velocity *= -1; // use correct formulas later
}

glm::vec2 Particle::GetPosition() {
  return position;
}
}

