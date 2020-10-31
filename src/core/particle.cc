#include "core/particle.h"

namespace idealgas{

Particle::Particle(size_t radius) {
  if(radius < 1) {
    throw std::invalid_argument("Not a valid radius");
  }
  radius_= radius;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

bool Particle::IsParticleCollision(const Particle& other_particle) const {
  glm::vec2 x2 = other_particle.GetPosition();
  glm::vec2 v2 = other_particle.GetVelocity();
  glm::vec2 particle_dist = position_ - x2;
  double dot_product = glm::dot(velocity_-v2, particle_dist);
  if (glm::length(particle_dist) <=  2*radius_ && dot_product < 0) {
    return true;
  }
  return false;
}

glm::vec2 Particle::CalculateVelocity(const Particle& other) const {
  glm::vec2 x2 = other.GetPosition();
  glm::vec2 v2 = other.GetVelocity();
  glm::vec2 particle_dist = position_ - x2;
  double dot_product = glm::dot(velocity_-v2, position_-x2);
  double denominator =
      glm::pow(glm::length(position_ - x2), 2);
  particle_dist *= dot_product / denominator;;
  glm::vec2 new_vel = velocity_ - particle_dist;

  // Can't set new velocity here - need to first calculate the new velocity
  // for the other particle using the original velocity of this particle
  return new_vel;
}

void Particle::CalculateWallCollisionVelocity
    (size_t particle_box_size, size_t window_margin) {
  if((position_.x + radius_ >= window_margin+ particle_box_size && velocity_.x > 0)
     || (position_.x - radius_ <= window_margin && velocity_.x < 0)){
    velocity_.x *= -1;
  }
  if((position_.y - radius_ <= window_margin && velocity_.y < 0)
     || (position_.y + radius_ >= window_margin+ particle_box_size && velocity_.y > 0)){
    velocity_.y *= -1;
  }
}

glm::vec2 Particle::GetPosition() const{
  return position_;
}

glm::vec2 Particle::GetVelocity() const {
  return velocity_;
}

size_t Particle::GetRadius() const {
  return radius_;
}

void Particle::SetPosition(const glm::vec2& pos) {
  position_ = pos;
}

void Particle::SetVelocity(const glm::vec2& vel) {
  velocity_ = vel;
}
} // namespace idealgas

