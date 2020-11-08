#ifndef IDEAL_GAS_HISTOGRAM_MANAGER_H
#define IDEAL_GAS_HISTOGRAM_MANAGER_H

#include "core/particle.h"
#include "core/histogram.h"
#include "map"
#include <math.h>


namespace idealgas {
using std::map;
using std::vector;
using glm::vec2;

/**
 * Handles all the different histograms that are a part of the simulation
 * Draws, Updates, and Clears them as appropriate
 */
class HistogramManager {
 public:

  /**
   * Initializes the three different histograms
   * @param upper_left_corner - holds the location of the upper left corner of
   *                            where the first histogram should be drawn
   */
  HistogramManager(const glm::vec2 &upper_left_corner);

  /**
   * Draws all histograms
   */
  void RenderHistograms();

  /**
   * Updates all the histograms' data by going through each particle and checking their speed
   * and then adding to the respective frequencies depending on the size of each particle
   * @param particles_ - list of all particles currently in the simulation
   */
  void UpdateHistograms(const vector<Particle>& particles_);

 private:

  const size_t kHistogramDist = 200; // Vertical distance between each histogram on the screen
  const size_t kHistogramSize = 100; // Size of a single Histogram (side length of square)

  /**
   * Resets all histograms on the screen to their original state with no bars
   */
  void ClearHistograms();

  Histogram small_histogram_; // Histogram representing speeds/frequencies of small particles
  Histogram med_histogram_; // Histogram representing speeds/frequencies of medium sized particles
  Histogram large_histogram_; // Histogram representing speeds/frequencies of large particles

};
} // namespace idealgas

#endif  // IDEAL_GAS_HISTOGRAM_MANAGER_H
