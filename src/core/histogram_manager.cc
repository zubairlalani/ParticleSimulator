#include "core/histogram_manager.h"

#include "visualizer/particle_box.h"

namespace idealgas{

HistogramManager::HistogramManager(const glm::vec2 &upper_left_corner)
    : small_histogram_(upper_left_corner, kHistogramSize, kHistogramSize, kSmallColor),
      med_histogram_(
          upper_left_corner + vec2(0, kHistogramDist + kHistogramSize),
          kHistogramSize,
          kHistogramSize,
          kMedColor),
      large_histogram_(
          upper_left_corner + vec2(0, 2* (kHistogramDist+kHistogramSize)),
          kHistogramSize,
          kHistogramSize,
          kLargeColor) {}

void HistogramManager::RenderHistograms() {
  small_histogram_.DrawHistogram();
  med_histogram_.DrawHistogram();
  large_histogram_.DrawHistogram();
  ClearHistograms();
}

void HistogramManager::UpdateHistograms(const vector<Particle>& particles) {
  for(size_t i = 0; i < particles.size(); i++) {
    float speed = roundf(glm::length(particles[i].GetVelocity()) * 10) / 10; //Rounding to the tenth

    if(particles[i].GetRadius() == idealgas::ParticleBox::kSmallParticleRadius) {
      small_histogram_.UpdateSpeedFrequency(speed);
    } else if (particles[i].GetRadius() == idealgas::ParticleBox::kMedParticleRadius) {
      med_histogram_.UpdateSpeedFrequency(speed);
    } else {
      large_histogram_.UpdateSpeedFrequency(speed);
    }
  }
}

const Histogram HistogramManager::GetSmallParticleHistogram() const {
  return small_histogram_;
}

const Histogram HistogramManager::GetMediumParticleHistogram() const {
  return med_histogram_;
}

const Histogram HistogramManager::GetLargeParticleHistogram() const {
  return large_histogram_;
}

void HistogramManager::ClearHistograms() {
  small_histogram_.Clear();
  med_histogram_.Clear();
  large_histogram_.Clear();
}

} // Namespace idealgas
