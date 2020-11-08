#ifndef IDEAL_GAS_PARTICLE_BOX_H
#define IDEAL_GAS_PARTICLE_BOX_H
#include "cinder/gl/gl.h"
#include "cinder/Color.h"
#include <core/particle.h>

namespace idealgas {
const ci::Color kSmallColor = ci::Color(0, 0, 100); // Color of particle box borders
const ci::Color kMedColor = ci::Color(0, 100, 0); // Color of particle box borders
const ci::Color kLargeColor = ci::Color(100, 0, 0); // Color of particle box borders

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
  void AddParticle(size_t id);

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

  const static size_t kSmallParticleRadius = 5; // Radius that all small particles have
  const static size_t kMedParticleRadius = 7; // Radius of medium sized particles
  const static size_t kLargeParticleRadius = 10; // Radius of large particles

  const ci::Color kSmallColor = ci::Color(0, 0, 100); // Color of particle box borders
  const ci::Color kMedColor = ci::Color(0, 100, 0); // Color of particle box borders
  const ci::Color kLargeColor = ci::Color(100, 0, 0); // Color of particle box borders
 private:
  const ci::Color kBoxColor = ci::Color::white(); // Color of particle box borders
  //const ci::Color kParticleColor = ci::Color(75, 0, 130); // Color of all the particles

  const float kSmallMass = 1; // mass of the smallest particle
  const float kMedMass = 5; // mass of the medium sized particle
  const float kLargeMass = 10; // mass of the largest particle
  glm::vec2 upper_left_corner_; // Top left corner of the particle box
  std::vector<Particle> particles_; // List of all particles within the box currently
  size_t pixels_x_; // Amount of pixels horizontally that the box stretches over
  size_t pixels_y_; // Amount of pixels vertically that the box stretches over
};

} // namespace idealgas

#endif  // IDEAL_GAS_PARTICLE_BOX_H
