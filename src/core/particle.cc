#include "core/particle.h"

namespace idealgas{

Particle::Particle(size_t radius, float mass) {
  if(radius < 1) {
    throw std::invalid_argument("Not a valid radius");
  }
  radius_= radius;
  mass_ = mass;
}

void Particle::UpdatePosition() {
  position_ += velocity_;
}

bool Particle::IsParticleCollision(const Particle& other_particle) const {
  glm::vec2 velocity_diff = velocity_ - other_particle.GetVelocity();
  glm::vec2 particle_dist = position_ - other_particle.GetPosition();
  double dot_product = glm::dot(velocity_diff, particle_dist);

  // When a particle collides they are at the most the sum of the radii away
  // dot_product < 0 makes sure the particles are moving towards each other
  if (glm::length(particle_dist) <=  other_particle.GetRadius()+radius_
      && dot_product < 0) {
    return true;
  }
  return false;
}

glm::vec2 Particle::CalculateVelocity(const Particle& other) const {
  // Using the particle collision equation:
  // v1' = v1 - dotproduct((v1-v2),(x1-x2))/||x1-x2||^2 * (x1 - x2)

  float m2 = other.GetMass();
  float mass_calc = 2*m2 / (mass_ + m2);

  glm::vec2 x2 = other.GetPosition();
  glm::vec2 velocity_diff = velocity_ - other.GetVelocity();
  glm::vec2 particle_dist = position_ - x2;
  double dot_product = glm::dot(velocity_diff, particle_dist);
  double denominator =
      glm::pow(glm::length(particle_dist), 2);
  particle_dist *= dot_product / denominator;;
  glm::vec2 new_vel = velocity_ - mass_calc*particle_dist;

  // Can't set new velocity here - need to first calculate the new velocity
  // for the other particle using the original velocity of this particle
  return new_vel;
}

void Particle::CalculateWallCollisionVelocity
    (size_t particle_box_size, size_t window_margin) {
  //Checking that the particle is touching the wall and moving towards each wall
  if((position_.x + radius_ >= window_margin+ particle_box_size && velocity_.x > 0) // Left and right walls
     || (position_.x - radius_ <= window_margin && velocity_.x < 0)){
    velocity_.x *= -1;
  }
  if((position_.y - radius_ <= window_margin && velocity_.y < 0)
     || (position_.y + radius_ >= window_margin+ particle_box_size && velocity_.y > 0)){ // top and bottom walls
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

float Particle::GetMass() const {
  return mass_;
}

void Particle::SetPosition(const glm::vec2& pos) {
  position_ = pos;
}

void Particle::SetVelocity(const glm::vec2& vel) {
  velocity_ = vel;
}
} // namespace idealgas

