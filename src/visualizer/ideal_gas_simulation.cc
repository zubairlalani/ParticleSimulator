#include <visualizer/ideal_gas_simulation.h>

namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp() {
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void NaiveBayesApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // light yellow
  ci::gl::clear(background_color);

  ci::gl::drawStringCentered(
      "IDEAL GAS SIMULATION",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));
}

void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
}

void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
