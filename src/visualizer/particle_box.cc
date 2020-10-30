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

void ParticleBox::Render(std::vector<idealgas::Particle>& particles) const {
  ci::gl::color(kBoxColor);
  ci::gl::drawSolidRect(ci::Rectf(upper_left_corner_, upper_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));
  for(size_t x = 0; x < particles.size(); x++) {
    particles[x].UpdatePosition();
    ci::gl::color (ci::Color::black());
    ci::gl::drawSolidCircle(particles[x].GetPosition(), 10);
  }
}

}