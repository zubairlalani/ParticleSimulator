#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"

namespace idealgas {

/**
 * A single particle within the simulation
 * Contains methods to appropriately update the
 * particle's velocity when collisions occur
 */
class Particle {
 public:

  /**
   * Initializes particle object with the specified radius
   * @param radius - radius of the particle
   */
  Particle(size_t radius, ci::Color color);

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

  /**
   * Calculates the velocity of particle based
   * on a collision with the given particle parameter
   * @param other_particle - the second particle part of the collision
   * @return calculated velocity as a vec2
   *         (can only set velocity after the velocity
   *          of the other particle is also calculated)
   */
  glm::vec2 CalculateVelocity(const Particle& other_particle) const;

  /**
   * Calculates and updates velocity of a particle when
   * it hits the wall of the particle box
   * @param particle_box_size - side length of square box that holds all the particles
   * @param window_margin - space between larger simulation screen and the the particle box
   */
  void CalculateWallCollisionVelocity(size_t particle_box_size, size_t window_margin);

  /**
   * Determines whether a particle is colliding with another given particle
   * @param other_particle - second particle part of the collision
   * @return true - if the particle is colliding with the given particle
   */
  bool IsParticleCollision(const Particle& other_particle) const;


 private:
  glm::vec2 position_ = glm::vec2(60, 60); // Keeps track of x and y coordinates
  glm::vec2 velocity_ = glm::vec2(2, 1); // Keeps track of x and y components of velocity_
  size_t radius_; // radius of a single circular particle
  ci::Color color_;

};
} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_H
