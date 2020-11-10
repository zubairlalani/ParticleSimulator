#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H

#include "cinder/gl/gl.h"
#include <map>

namespace idealgas {

using std::map;

/**
 * A single histogram within the simulation
 */
class Histogram {
 public:

  Histogram(const glm::vec2 &upper_left_corner,
            size_t pixels_x,
            size_t pixels_y, const ci::Color& color);

  /**
   * Using the stored speeds and the frequency that they occur,
   * draws the histogram onto the screen
   */
  void DrawHistogram();

  /**
   * Increments the number of particles (frequency) that have the given speed
   * @param speed - Speed of a single particle
   */
  void UpdateSpeedFrequency(float speed);

  /**
   * Resets histogram; Clears all the rectangles from the histogram
   */
  void Clear();

  /**
   * Gets the frequency that each speed for a given particle type appears
   * @return map - key is the speed and the value is the frequency that a particle has a speed
   */
  const map<float, size_t> GetSpeedFrequencies() const;

  /**
   * Gets the location of the upper left corner of the histogram box
   * @return vec2 - point that indicates the upper left corner of the histogram
   */
  const glm::vec2 GetUpperLeftCorner() const;

  /**
   * Gets the width and height of the box - for testing
   * @return Dimensions of the histogram box as a vec2
   */
  const glm::vec2 GetDimensions() const;

 private:

  const int kYLabelMargin = 35; // Distance to left of the y axis that the y label is drawn
  const size_t kXLabelMargin = 20; // Distance below the x axis that the x label is drawn
  const int kRectangleWidth = 5; // Width of each rectangle within the histogram
  const size_t kRectMultiplier = 10; // Number that the frequencies are multiplied
                                     // by in order to create the height of each rectangle
  /**
   * Draws each of the rectangles within a single histogram based
   * on the frequencies of all distinct speeds (of a given type of particle)
   */
  void DrawHistRects();

  map<float, size_t> speed_frequency_; // Maps each speed of a type of particle to the amount of particles that have that speed
  glm::vec2 upper_left_corner_; // Top left corner of a histogram box
  size_t pixels_x_; // Amount of pixels horizontally that the box stretches over
  size_t pixels_y_; // Amount of pixels vertically that the box stretches over
  ci::Color histogram_color_; // color of this histogram (same as the type of particle it is representing)
};
}

#endif  // IDEAL_GAS_HISTOGRAM_H
