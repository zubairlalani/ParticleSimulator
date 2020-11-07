#include <visualizer/ideal_gas_simulation.h>

namespace idealgas {

namespace visualizer {

IdealGasSimulation::IdealGasSimulation()
    : particle_box_(
          glm::vec2(kMargin,kMargin),
          kParticleBoxSize,
          kParticleBoxSize
          ),
      histogram_generator_(
          glm::vec2(kLeftHistogramMargin, kMargin),
          kHistogramSize,
          kHistogramSize
          ){
  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasSimulation::setup() {
  mParams = ci::params::InterfaceGl::create(
      getWindow(), "App parameters",
      getWindow()->toPixels( ci::ivec2( 400, 120 ) )
      );
  mParams->setPosition(glm::vec2(50, 500));
  mParams->addButton("Small Particle", [ & ]() { button( 0 ); });
  mParams->addButton("Medium Particle", [ & ]() { button( 1 ); });
  mParams->addButton("Large Particle", [ & ]() { button( 2 ); });
  mParams->addButton("Increase Speed", [ & ]() { button( 3 ); });
  mParams->addButton("Decrease Speed", [ & ]() { button( 4 ); });
  mParams->addButton("Clear", [ & ]() { button( 5 ); });
}

void IdealGasSimulation::draw() {
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);
  ci::gl::drawStringCentered(
      "IDEAL GAS SIMULATION",
      glm::vec2(kWindowSize / 2, kMargin / 2),
      ci::Color("white")); // Creates title at the top of the screen

  particle_box_.RenderParticles();
  histogram_generator_.RenderHistograms();

  mParams->draw();
}

void IdealGasSimulation::update() {
  particle_box_.UpdateParticles(kMargin);
  histogram_generator_.UpdateHistograms(particle_box_.GetParticles());
}

void IdealGasSimulation::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_SPACE:
      particle_box_.AddParticle(0);
      break;

    case ci::app::KeyEvent::KEY_1:
      particle_box_.AddParticle(1);
      break;

    case ci::app::KeyEvent::KEY_2:
      particle_box_.AddParticle(2);
      break;

    case ci::app::KeyEvent::KEY_BACKSPACE:
      particle_box_.Clear();
      break;

    case ci::app::KeyEvent::KEY_UP:
      particle_box_.IncreaseDecreaseSpeed(kSpeedUpFactor);
      break;

    case ci::app::KeyEvent::KEY_DOWN:
      particle_box_.IncreaseDecreaseSpeed(kSlowDownFactor);
      break;
  }
}

void IdealGasSimulation::button(size_t id) {
  if(id < 3) {
    particle_box_.AddParticle(id);
  } else if(id == 3) {
    particle_box_.IncreaseDecreaseSpeed(kSpeedUpFactor);
  } else if(id == 4) {
    particle_box_.IncreaseDecreaseSpeed(kSlowDownFactor);
  } else {
    particle_box_.Clear();
  }
}
}  // namespace visualizer
}  // namespace idealgas
