#include "core/histogram_generator.h"

#include "visualizer/particle_box.h"

namespace idealgas{

HistogramGenerator::HistogramGenerator(const glm::vec2 &upper_left_corner,
                     size_t pixels_x,
                     size_t pixels_y)
    : upper_left_corner_(upper_left_corner),
      pixels_x_(pixels_x),
      pixels_y_(pixels_y) {}

void HistogramGenerator::RenderHistograms() {
  ci::gl::color(0, 0, 100);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_, upper_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_+glm::vec2(pixels_x_/2, pixels_y_+20),
      ci::Color("white"));

  ci::gl::color(0, 100, 0);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_ + glm::vec2(0, 200), upper_left_corner_ + ci::vec2(pixels_x_, 200 + pixels_y_)));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_+glm::vec2(pixels_x_/2, pixels_y_+220),
      ci::Color("white"));

  ci::gl::color(100, 0, 0);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_ + glm::vec2(0, 400), upper_left_corner_ + ci::vec2(pixels_x_, 400 + pixels_y_)));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_+glm::vec2(pixels_x_/2, pixels_y_+420),
      ci::Color("white"));

  ci::gl::color(0, 0, 100);
  ci::vec2 topLeft(upper_left_corner_ + ci::vec2(0, pixels_y_));
  map<float, size_t>::iterator it;
  for ( it = small_speed_frequency_.begin(); it != small_speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(ci::Rectf(topLeft, topLeft - ci::vec2(-5, 10*small_speed_frequency_[it->first])));
    topLeft += ci::vec2(2, 0);
  }

  ci::gl::color(0, 100, 0);
  topLeft = ci::vec2(upper_left_corner_ + glm::vec2(0, 200+pixels_y_));
  for ( it = med_speed_frequency_.begin(); it != med_speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(ci::Rectf(topLeft, topLeft - ci::vec2(-5, 10*med_speed_frequency_[it->first])));
    topLeft += ci::vec2(2, 0);
  }

  ci::gl::color(100, 0, 0);
  topLeft = ci::vec2(upper_left_corner_ + glm::vec2(0, 400+pixels_y_));
  for ( it = large_speed_frequency_.begin(); it != large_speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(ci::Rectf(topLeft, topLeft - ci::vec2(-5, 10*large_speed_frequency_[it->first])));
    topLeft += ci::vec2(2, 0);
  }

  small_speed_frequency_.clear();
  med_speed_frequency_.clear();
  large_speed_frequency_.clear();
}

void HistogramGenerator::UpdateHistograms(const vector<Particle>& particles) {
  for(size_t i = 0; i < particles.size(); i++) {
    float speed = roundf(glm::length(particles[i].GetVelocity()) * 10) / 10;

    if(particles[i].GetRadius() == idealgas::ParticleBox::kSmallParticleRadius) {
      if(small_speed_frequency_.find(speed)== small_speed_frequency_.end()) {
        small_speed_frequency_[speed] = 1;
      } else {
        small_speed_frequency_[speed]++;
      }
    } else if (particles[i].GetRadius() == idealgas::ParticleBox::kMedParticleRadius) {
      if(med_speed_frequency_.find(speed) == med_speed_frequency_.end()) {
        med_speed_frequency_[speed] = 1;
      } else {
        med_speed_frequency_[speed]++;
      }
    } else {
      if(large_speed_frequency_.find(speed) == large_speed_frequency_.end()) {
        large_speed_frequency_[speed] = 1;
      }
      else {
        large_speed_frequency_[speed]++;
      }
    }
  }
}

}
