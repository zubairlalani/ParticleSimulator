#ifndef IDEAL_GAS_PARTICLE_BOX_H
#define IDEAL_GAS_PARTICLE_BOX_H
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include <core/particle.h>

namespace idealgas {

/**
 * Draws/Contains all particles and makes sure that each particle's
 * position and velocity is updated each frame
 */
class ParticleBox {

 public:

  /**
   * Initializes the dimensions needed to create the particle box
   * @param upper_left_corner - Coordinates of the top left corner of the particle box
   * @param pixels_x - Amount of pixels in x direction that the particle box spans
   * @param pixels_y - Amount of pixels in y direction that the particle box spans
   */
  ParticleBox(const glm::vec2 &upper_left_corner,
                size_t pixels_x,
                size_t pixels_y);

  /**
   * Draws the particle box and all the particles that it contains
   */
  void RenderParticles();

  /**
   * Updates all particle positions based on their current velocities
   * Updates each particle's velocity based on
   * what collisions occurred (walls and other particles)
   * @param kMargin Amount of indentation that
   *        particle box has within the larger simulation screen
   */
  void UpdateParticles(size_t kMargin);

  /**
   * Adds a particle to the particle_box/simulation
   */
  void AddParticle();

  /**
   * Clears all the particles from the box
   */
  void Clear();

  /**
   * Gets the vector of all the particles within the particle box
   * @return vector of particle objects
   */
  const std::vector<Particle> GetParticles();

  /**
   * Speeds up or slows down all particles on the screen
   * @param speed_factor - how much the all the particles speed increases by
   */
  void IncreaseDecreaseSpeed(float speed_factor);

 private:

  const ci::Color kBoxColor = ci::Color::white(); // Color of particle box borders
  const ci::Color kParticleColor = ci::Color(75, 0, 130); // Color of all the particles
  const size_t kParticleRadius = 5; // Radius that each particle will have --> update during week2
  glm::vec2 upper_left_corner_; // Top left corner of the particle box
  std::vector<Particle> particles_; // List of all particles within the box currently
  size_t pixels_x_; // Amount of pixels horizontally that the box stretches over
  size_t pixels_y_; // Amount of pixels vertically that the box stretches over
};
} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_BOX_H
