#include "visualizer/particle_box.h"

namespace idealgas{
using glm::vec2;
using ci::Color;

ParticleBox::ParticleBox(const glm::vec2 &upper_left_corner,
                         size_t pixels_x,
                         size_t pixels_y)
    : upper_left_corner_(upper_left_corner),
      pixels_x_(pixels_x),
      pixels_y_(pixels_y){}

void ParticleBox::RenderParticles() {
  ci::gl::color(kBoxColor);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_, upper_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));

  // Draws all particles onto screen
  for(auto & particle : particles_) {
    if(particle.GetRadius() == kSmallParticleRadius) {
      ci::gl::color (kSmallColor); // Blueish
      ci::gl::drawSolidCircle(particle.GetPosition(), kSmallParticleRadius);
    } else if(particle.GetRadius() == kMedParticleRadius) {
      ci::gl::color (kMedColor); // Greenish
      ci::gl::drawSolidCircle(particle.GetPosition(), kMedParticleRadius);
    } else {
      ci::gl::color (kLargeColor); // Reddish
      ci::gl::drawSolidCircle(particle.GetPosition(), kLargeParticleRadius);
    }
  }
}

void ParticleBox::UpdateParticles(size_t kMargin) {
  for(size_t i = 0; i < particles_.size(); i++) {
    particles_[i].UpdatePosition();
    particles_[i].CalculateWallCollisionVelocity(pixels_x_, kMargin);

    for(size_t j = i; j < particles_.size(); j++) {
      // Makes sure that it doesn't check for a collision between a particle and itself
      if(particles_.size() > 1
         && particles_[i].GetPosition() != particles_[j].GetPosition()) {

        if(particles_[i].IsParticleCollision(particles_[j])) {
          glm::vec2 new_vel = particles_[i].CalculateVelocity(particles_[j]);
          glm::vec2 new_vel2 = particles_[j].CalculateVelocity(particles_[i]);
          particles_[i].SetVelocity(new_vel);
          particles_[j].SetVelocity(new_vel2);
        }
      }
    }
  }
}

void ParticleBox::AddParticle(size_t id) {
  if(id == 0)
    particles_.emplace_back(Particle(kSmallParticleRadius, kSmallMass));
  else if (id == 1) {
    particles_.emplace_back(Particle(kMedParticleRadius, kMedMass));
  } else {
    particles_.emplace_back(Particle(kLargeParticleRadius, kLargeMass));
  }
}

void ParticleBox::Clear() {
  particles_.clear();
}

const std::vector<Particle> ParticleBox::GetParticles() {
  return particles_;
}

void ParticleBox::IncreaseDecreaseSpeed(float speed_factor) {
  for(auto & particle : particles_) {
    vec2 new_velocity = speed_factor * particle.GetVelocity();
    particle.SetVelocity(new_velocity);
  }
}
} // namespace idealgas