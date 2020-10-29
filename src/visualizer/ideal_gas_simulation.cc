#include <visualizer/ideal_gas_simulation.h>

namespace idealgas {

namespace visualizer {

IdealGasSimulation::IdealGasSimulation() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasSimulation::draw() {
  ci::Color8u background_color(0, 0, 0);  // light yellow
  ci::gl::clear(background_color);

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
      break;

    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace visualizer

}  // namespace idealgas
