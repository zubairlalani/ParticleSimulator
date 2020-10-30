#include <visualizer/ideal_gas_simulation.h>

namespace idealgas {

namespace visualizer {

IdealGasSimulation::IdealGasSimulation()
    : particle_box_(
          glm::vec2(kMargin,kMargin),
          500,
          500
          ){
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasSimulation::draw() {
  ci::Color8u background_color(0, 0, 0);  // light yellow
  ci::gl::clear(background_color);

  particle_box_.Render(particles);
  ci::gl::drawStringCentered(
      "IDEAL GAS SIMULATION",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));
}

void IdealGasSimulation::mouseDown(ci::app::MouseEvent event) {
}

void IdealGasSimulation::mouseDrag(ci::app::MouseEvent event) {
}

void IdealGasSimulation::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      particles.emplace_back(Particle());
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
