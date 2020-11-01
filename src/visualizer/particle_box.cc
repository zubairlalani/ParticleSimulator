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
    ci::gl::color (kParticleColor); // Pink/Purplish color
    ci::gl::drawSolidCircle(particle.GetPosition(), kParticleRadius);
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

void ParticleBox::AddParticle() {
  //TODO Add radius based on mass for week2
  particles_.emplace_back(Particle(kParticleRadius));
}

void ParticleBox::Clear() {
  particles_.clear();
}

const std::vector<Particle> ParticleBox::GetParticles() {
  return particles_;
}

void ParticleBox::IncreaseDecreaseSpeed(size_t speed_factor) {
  for(auto & particle : particles_) {
    int x_increment_value = speed_factor;
    int y_increment_value = speed_factor;
    if(particle.GetVelocity().x < 0){
      x_increment_value*=-1;
    }
    if(particle.GetVelocity().y < 0) {
      y_increment_value*=-1;
    }

    vec2 increment_vect = vec2(x_increment_value, y_increment_value);
    vec2 new_velocity = increment_vect+particle.GetVelocity();

    vec2 same_dir_test = vec2(new_velocity.x * particle.GetVelocity().x,
                              new_velocity.y * particle.GetVelocity().y);

    // Ensures that the direction doesn't reverse at low speeds
    // one of the components of the new speed can reach zer
    if((same_dir_test.x >= 0
        && same_dir_test.y >= 0)
        && !(same_dir_test.x == 0 && same_dir_test.y == 0)) {
      particle.SetVelocity(new_velocity);
    }

  }
}
} // namespace idealgas