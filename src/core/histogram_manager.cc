#include "core/histogram_manager.h"

#include "visualizer/particle_box.h"

namespace idealgas{

HistogramGenerator::HistogramGenerator(const glm::vec2 &upper_left_corner,
                     size_t pixels_x,
                     size_t pixels_y)
    : upper_left_corner_(upper_left_corner),
      pixels_x_(pixels_x),
      pixels_y_(pixels_y) {}

void HistogramGenerator::RenderHistograms() {
  DrawSmallHistogram();
  DrawMedHistogram();
  DrawLargeHistogram();
  ClearFrequencyMaps();
}

void HistogramGenerator::UpdateHistograms(const vector<Particle>& particles) {
  for(size_t i = 0; i < particles.size(); i++) {
    float speed = roundf(glm::length(particles[i].GetVelocity()) * 10) / 10; //Rounding to the tenth

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

void HistogramGenerator::DrawSmallHistRects() {
  ci::gl::color(kSmallColor);
  ci::vec2 topLeft(upper_left_corner_ + ci::vec2(0, pixels_y_));
  map<float, size_t>::iterator it;
  for ( it = small_speed_frequency_.begin(); it != small_speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(ci::Rectf
         (topLeft, topLeft - ci::vec2(-kRectangleWidth,
                                    kRectMultiplier *small_speed_frequency_[it->first]))
         );
    topLeft += ci::vec2(kRectangleWidth, 0);
  }
}

void HistogramGenerator::DrawMedHistRects() {
  ci::gl::color(kMedColor);
  ci::vec2 topLeft = ci::vec2(upper_left_corner_ + glm::vec2(0, kHistogramDist+pixels_y_));
  map<float, size_t>::iterator it;
  for ( it = med_speed_frequency_.begin(); it != med_speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(
        ci::Rectf(topLeft, topLeft - ci::vec2(-kRectangleWidth,
                           kRectMultiplier *med_speed_frequency_[it->first]))
        );
    topLeft += ci::vec2(kRectangleWidth, 0);
  }
}

void HistogramGenerator::DrawLargeHistRects() {
  ci::gl::color(kLargeColor);
  ci::vec2 topLeft = ci::vec2(upper_left_corner_ + glm::vec2(0, 2*kHistogramDist+pixels_y_));
  map<float, size_t>::iterator it;
  for ( it = large_speed_frequency_.begin(); it != large_speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(ci::Rectf(
            topLeft,topLeft - ci::vec2(-kRectangleWidth,
                                    kRectMultiplier *large_speed_frequency_[it->first]))
        );
    topLeft += ci::vec2(kRectangleWidth, 0);
  }
}

void HistogramGenerator::ClearFrequencyMaps() {
  small_speed_frequency_.clear();
  med_speed_frequency_.clear();
  large_speed_frequency_.clear();
}

void HistogramGenerator::DrawSmallHistogram() {
  ci::gl::color(kSmallColor);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_, upper_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));
  ci::gl::drawStringCentered(
      "Frequency",
      upper_left_corner_+glm::vec2(-kYLabelMargin, pixels_y_/2),
      ci::Color(kSmallColor));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_ + glm::vec2(pixels_x_/2, pixels_y_+kXLabelMargin),
      ci::Color(kSmallColor));

  DrawSmallHistRects();
}

void HistogramGenerator::DrawMedHistogram() {
  ci::gl::color(kMedColor);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_ + glm::vec2(0, kHistogramDist), upper_left_corner_ + ci::vec2(pixels_x_, kHistogramDist + pixels_y_)));

  ci::gl::drawStringCentered(
      "Frequency",
      upper_left_corner_+ glm::vec2(-kYLabelMargin, kHistogramDist + pixels_y_/2),
      ci::Color(kMedColor));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_+glm::vec2(pixels_x_/2, pixels_y_+kHistogramDist+kXLabelMargin),
      ci::Color(kMedColor));

  DrawMedHistRects();
}

void HistogramGenerator::DrawLargeHistogram() {
  ci::gl::color(kLargeColor);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_ + glm::vec2(0, 2*kHistogramDist), upper_left_corner_ + ci::vec2(pixels_x_, 2*kHistogramDist + pixels_y_)));

  ci::gl::drawStringCentered(
      "Frequency",
      upper_left_corner_+glm::vec2(-kYLabelMargin, 2*kHistogramDist + pixels_y_/2),
      ci::Color(kLargeColor));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_+glm::vec2(pixels_x_/2, pixels_y_+2*kHistogramDist+kXLabelMargin),
      ci::Color(kLargeColor));

  DrawLargeHistRects();
}

}
