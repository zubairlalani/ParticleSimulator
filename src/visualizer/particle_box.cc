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

void ParticleBox::Render() {
  ci::gl::color(kBoxColor);
  ci::gl::drawStrokedRect(ci::Rectf(upper_left_corner_, upper_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));
  for(size_t x = 0; x < particles_.size(); x++) {
    particles_[x].UpdatePosition();
    ci::gl::color (75, 0, 130);
    ci::gl::drawSolidCircle(particles_[x].GetPosition(), kParticleRadius);
  }
}

void ParticleBox::UpdateParticleVelocities(size_t kMargin) {
  for(size_t x = 0; x < particles_.size(); x++) {
    particles_[x].CalculateWallCollisionVelocity(pixels_x_, kMargin);

    for(size_t y = x; y < particles_.size(); y++) {
      // Makes sure that it doesn't check for a collision between a particle and itself
      if(particles_.size() > 1
         && particles_[x].GetPosition() != particles_[y].GetPosition()) {
        if(particles_[x].IsParticleCollision(particles_[y])) {
          glm::vec2 new_vel = particles_[x].CalculateVelocity(particles_[y]);
          glm::vec2 new_vel2 = particles_[y].CalculateVelocity(particles_[x]);
          particles_[x].SetVelocity(new_vel);
          particles_[y].SetVelocity(new_vel2);
        }
      }
    }
  }
}

void ParticleBox::AddParticle() {
  particles_.emplace_back(Particle(kParticleRadius)); // For now set to radius 10 --> implement different sizes during week 2
}

void ParticleBox::Clear() {
  particles_.clear();
}
}