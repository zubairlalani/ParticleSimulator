#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"

namespace idealgas {
class Particle {
 public:
  /**
   * Updates position based on the velocity of the Particle
   * assuming that one unit of time has passed
   */
  void UpdatePosition();

  /**
   * Changes velocity when the Particle encounters a wall, or another Particle
   */
  void UpdateVelocity();

  /**
   * Gets the x and y coordinates of the particle in the form of vec2
   * @return 2d vector representing x and y coordinates of particle
   */
  glm::vec2 GetPosition();
 private:
  glm::vec2 position = glm::vec2(50, 50 ); // Keeps track of x and y coordinates
  glm::vec2 velocity = glm::vec2(1, 1); // Keeps track of x and y components of velocity

};
} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_H
