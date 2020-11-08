#pragma once

#include <string>
#include <vector>

#include "cinder/Camera.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "core/histogram_manager.h"
#include "core/particle.h"
#include "visualizer/particle_box.h"

using std::vector;

namespace idealgas {

namespace visualizer {

/**
 * Runs the whole simulation and contains all the different parts such the
 * particle box and the three histograms
 */
class IdealGasSimulation : public ci::app::App {
 public:

  /**
   * Initializes simulation screen and particle box
   */
   IdealGasSimulation();

   /**
    * Cinder method that runs each continuously
    * Updates the simulation state (Each particle's position/velocity and the histograms)
    */
   void update() override;

   /**
    * Draws everything on the simulation screen
    */
   void draw() override;

   /**
    * Adds particles to the simulation or clears them all
    * @param event - the action of pressing space or backspace
    */
   void keyDown(ci::app::KeyEvent event) override;

   void button(size_t id);

   void setup() override;

 private:
  const size_t kWindowSize = 700; // Size of the overall simulation window
  const size_t kMargin = 50; // Margins of the particle box from the simulation window
  const size_t kLeftHistogramMargin = 550; // Distance from left that the Histogram starts
  const size_t kParticleBoxSize = 400; // Side length of the Particle Box
  const size_t kHistogramSize = 100; // Size of a single Histogram
  const float kSpeedUpFactor = 1.1f; // How much speed of particles increases for every up key
  const float kSlowDownFactor = .9f; // How much speed decreases for every down key is pressed
  idealgas::ParticleBox particle_box_; // Box on screen that holds all particles
  idealgas::HistogramManager histogram_generator_; // Creates histograms that show frequency of each speed for different particle types
  ci::params::InterfaceGlRef mParams; // Holds buttons for adding particles
};
}  // namespace visualizer
}  // namespace idealgas
