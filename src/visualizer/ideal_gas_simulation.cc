#include <visualizer/ideal_gas_simulation.h>

namespace idealgas {

namespace visualizer {

IdealGasSimulation::IdealGasSimulation()
    : particle_box_(
          glm::vec2(kMargin,kMargin),
          kParticleBoxSize,
          kParticleBoxSize
          ){
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasSimulation::draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);
  ci::gl::drawStringCentered(
      "IDEAL GAS SIMULATION",
      glm::vec2(kWindowSize / 2, kMargin / 2),
      ci::Color("white"));

  particle_box_.Render();

}

void IdealGasSimulation::update() {
  particle_box_.UpdateParticleVelocities(kMargin);
}

void IdealGasSimulation::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      particle_box_.AddParticle();
      break;

    case ci::app::KeyEvent::KEY_BACKSPACE:
      particle_box_.Clear();
      break;
  }
}
}  // namespace visualizer
}  // namespace idealgas
