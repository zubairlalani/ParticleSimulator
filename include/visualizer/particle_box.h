#ifndef IDEAL_GAS_PARTICLE_BOX_H
#define IDEAL_GAS_PARTICLE_BOX_H
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include <core/particle.h>

namespace idealgas {
class ParticleBox {
 public:
  ParticleBox(const glm::vec2 &upper_left_corner,
                size_t pixels_x,
                size_t pixels_y);

  void Render(std::vector<idealgas::Particle>& particles) const;

  void Clear();

 private:
  const ci::Color kBoxColor = ci::Color::white();
  glm::vec2 upper_left_corner_;
  size_t pixels_x_;
  size_t pixels_y_;

};
}

#endif  // IDEAL_GAS_PARTICLE_BOX_H
