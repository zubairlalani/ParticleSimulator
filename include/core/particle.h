#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"

namespace idealgas {
class Particle {
 public:

  Particle(size_t radius);

  /**
   * Updates position based on the velocity_ of the Particle
   * assuming that one unit of time has passed
   */
  void UpdatePosition();

  /**
   * Gets the x and y coordinates of the particle in the form of vec2
   * @return 2d (math) vector representing x and y coordinates of particle
   */
  glm::vec2 GetPosition() const;

  /**
   * Get x and y components of velocity_ as a vec2
   * @return 2d (math) vector representing x and y velocity components
   */
  glm::vec2 GetVelocity() const;

  /**
   * Gets the radius of the particle as a size_t
   * @return size_t radius of the particle
   */
  size_t GetRadius() const;

  /**
   * Sets position_ of particle to the given position (x and y coordinates)
   * @param pos - location that the particle will be set to
   */
  void SetPosition(const glm::vec2& pos);

  /**
   * Sets velocity_ to the given vec2 (x and y velocity components)
   * @param vel x and y components of velocity represented as a vec2
   */
  void SetVelocity(const glm::vec2& vel);


  glm::vec2 CalculateVelocity(const Particle& other_particle);

  void CalculateWallCollisionVelocity(size_t window_size, size_t window_margin);

  bool IsParticleCollision(const Particle& other_particle);


 private:
  glm::vec2 position_ = glm::vec2(60, 60); // Keeps track of x and y coordinates
  glm::vec2 velocity_ = glm::vec2(2, 1); // Keeps track of x and y components of velocity_
  size_t radius_; // radius of a single circular particle


};
} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_H
