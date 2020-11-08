#ifndef IDEAL_GAS_HISTOGRAM_MANAGER_H
#define IDEAL_GAS_HISTOGRAM_MANAGER_H

#include "core/particle.h"
#include "map"
#include <math.h>

using std::map;
using std::vector;

namespace idealgas {

/**
 * A single Histogram that keeps track of the frequency
 * of particles with each speed for a type of particle
 */
class HistogramGenerator {
 public:
  HistogramGenerator(const glm::vec2 &upper_left_corner,
            size_t pixels_x,
            size_t pixels_y);

  void RenderHistograms();

  void UpdateHistograms(const vector<Particle>& particles_);


 private:

  const int kYLabelMargin = 35;
  const size_t kXLabelMargin = 20;
  const size_t kHistogramDist = 200;
  const int kRectangleWidth = 5;
  const size_t kRectMultiplier = 10;

  void DrawSmallHistRects();
  void DrawMedHistRects();
  void DrawLargeHistRects();
  void DrawSmallHistogram();
  void DrawMedHistogram();
  void DrawLargeHistogram();
  void ClearFrequencyMaps();

  map<float, size_t> small_speed_frequency_; // Maps each speed of a type of particle to the amount of particles that have that speed
  map<float, size_t> med_speed_frequency_;
  map<float, size_t> large_speed_frequency_;
  glm::vec2 upper_left_corner_; // Top left corner of the particle box
  std::vector<Particle> particles_; // List of all particles within the box currently
  size_t pixels_x_; // Amount of pixels horizontally that the box stretches over
  size_t pixels_y_; // Amount of pixels vertically that the box stretches over

};
} // namespace idealgas

#endif  // IDEAL_GAS_HISTOGRAM_MANAGER_H
