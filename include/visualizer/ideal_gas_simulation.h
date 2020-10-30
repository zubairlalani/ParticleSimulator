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

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  const double kWindowSize = 675;
  const double kMargin = 50;

 private:
  std::vector<idealgas::Particle> particles;
  idealgas::ParticleBox particle_box_;

};

}  // namespace visualizer

}  // namespace idealgas
