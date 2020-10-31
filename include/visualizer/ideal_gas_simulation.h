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
 * Allows a user to draw a digit on a sketchpad and uses Naive Bayes to
 * classify it.
 */
class IdealGasSimulation : public ci::app::App {
 public:

  /**
   * Initializes sketchpad and model
   */
   IdealGasSimulation();
   void update() override;
   void draw() override;
   void keyDown(ci::app::KeyEvent event) override;

 private:
  const size_t kWindowSize = 700;
  const size_t kMargin = 50;
  const size_t kParticleBoxSize = 400;

  idealgas::ParticleBox particle_box_; // Box on screen that holds all particles
};

}  // namespace visualizer

}  // namespace idealgas
