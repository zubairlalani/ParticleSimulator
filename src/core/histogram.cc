#include "core/histogram.h"
namespace idealgas {

Histogram::Histogram(const glm::vec2 &upper_left_corner,
                     size_t pixels_x,
                     size_t pixels_y, const ci::Color& color)
    : upper_left_corner_(upper_left_corner),
      pixels_x_(pixels_x),
      pixels_y_(pixels_y),
      histogram_color_(color){}

void Histogram::UpdateSpeedFrequency(float speed) {
  if(speed_frequency_.find(speed)== speed_frequency_.end()) {
    speed_frequency_[speed] = 1;
  } else {
    speed_frequency_[speed]++;
  }
}

void Histogram::DrawHistRects() {
  ci::gl::color(histogram_color_);
  ci::vec2 topLeft(upper_left_corner_ + ci::vec2(0, pixels_y_));
  map<float, size_t>::iterator it;
  for ( it = speed_frequency_.begin(); it != speed_frequency_.end(); it++) {
    ci::gl::drawSolidRect(ci::Rectf
                              (topLeft, topLeft - ci::vec2(-kRectangleWidth,
                                                           kRectMultiplier *speed_frequency_[it->first]))
    );
    topLeft += ci::vec2(kRectangleWidth, 0);
  }
}

void Histogram::DrawHistogram() {
  ci::gl::color(histogram_color_);
  ci::gl::drawStrokedRect(ci::Rectf(
      upper_left_corner_, upper_left_corner_ + ci::vec2(pixels_x_, pixels_y_)));
  ci::gl::drawStringCentered(
      "Frequency",
      upper_left_corner_+glm::vec2(-kYLabelMargin, pixels_y_/2),
      ci::Color(histogram_color_));

  ci::gl::drawStringCentered(
      "Speed",
      upper_left_corner_ + glm::vec2(pixels_x_/2, pixels_y_+kXLabelMargin),
      ci::Color(histogram_color_));

  DrawHistRects();
}

void Histogram::Clear() {
  speed_frequency_.clear();
}
}