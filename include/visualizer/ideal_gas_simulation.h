#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/particle.h"
#include "visualizer/particle_box.h"
#include <string>
#include <vector>

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

 private:
  const size_t kWindowSize = 700; // Size of the overall simulation window
  const size_t kMargin = 50; // Margins of the particle box from the simulation window
  const size_t kParticleBoxSize = 400; // Side length of the Particle Box

  idealgas::ParticleBox particle_box_; // Box on screen that holds all particles
};
}  // namespace visualizer
}  // namespace idealgas
