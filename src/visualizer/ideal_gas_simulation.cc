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
  ci::Color8u background_color(0, 0, 0);
  ci::gl::clear(background_color);

  particle_box_.Render(particles);

  for(size_t x = 0; x < particles.size(); x++) {
    if(particles[x].GetPosition().x + 5 > kMargin+480
       || particles[x].GetPosition().x - 5 < kMargin + 10 ){
      particles[x].UpdateVelocity(true);
    }
    if(particles[x].GetPosition().y - 5 < kMargin + 10
       || particles[x].GetPosition().y + 5 > kMargin+480){
      particles[x].UpdateVelocity(false);
    }

    for(size_t y = 1; y < particles.size(); y++) {
      if(particles.size() > 1 && particles[x].GetPosition() != particles[y].GetPosition() && particles[x].GetVelocity() != particles[y].GetVelocity()) {

        glm::vec2 x1 = particles[x].GetPosition();
        glm::vec2 x2 = particles[y].GetPosition();
        glm::vec2 particle_dist = x1 - x2;

        glm::vec2 v1 = particles[x].GetVelocity();
        glm::vec2 v2 = particles[y].GetVelocity();
        //bool opposite = (v1.x >0 && v2.x < 0) || (v1.x < 0 && v2.x > 0) || (v1.y > 0 && v2.y < 0) || (v1.y < 0 && v2.y > 0);
        if (glm::length(particle_dist) <=  10 && glm::dot(v1-v2, x1-x2) < 0) {

          double dot_product = glm::dot((v1 - v2), (x1 - x2));
          double length_squared = glm::pow(glm::length(x1 - x2), 2);
          double division = dot_product / length_squared;
          particle_dist *= division;
          glm::vec2 new_vel = v1 - particle_dist;


          double dot_product2 = glm::dot((v2 - v1), (x2 - x1));
          double length_squared2 = glm::pow(glm::length(x2 - x1), 2);
          double division2 = dot_product2 / length_squared2;
          glm::vec2 particle_dist2 = x2 - x1;
          particle_dist2 *= division2;
          glm::vec2 new_vel2 = v1 - particle_dist2;

          particles[x].SetVelocity(new_vel);
          particles[y].SetVelocity(new_vel2);

        }
      }
    }
  }

  ci::gl::drawStringCentered(
      "IDEAL GAS SIMULATION",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));
}

void IdealGasSimulation::update() {

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
