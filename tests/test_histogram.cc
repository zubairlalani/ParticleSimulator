#include <catch2/catch.hpp>
#include "core/histogram.h"
#include "core/histogram_manager.h"
#include "core/particle.h"

TEST_CASE("Histogram constructor sets dimensions correctly") {
  idealgas::Histogram histogram(
      glm::vec2(50, 71), 60, 110,
      ci::Color(100, 100, 100));

  REQUIRE(histogram.GetDimensions().x == 60);
  REQUIRE(histogram.GetDimensions().y == 110);
  REQUIRE(histogram.GetUpperLeftCorner().x == 50);
  REQUIRE(histogram.GetUpperLeftCorner().y == 71);
}

TEST_CASE("Updating and clearing individual histograms") {

  idealgas::Histogram histogram(
      glm::vec2(50, 50), 100, 100,
      ci::Color(100, 100, 100));

  REQUIRE(histogram.GetSpeedFrequencies().size() == 0); // Initially histogram is empty
  histogram.UpdateSpeedFrequency(23.1f);

  REQUIRE(histogram.GetSpeedFrequencies().at(23.1f) == 1);
  REQUIRE(histogram.GetSpeedFrequencies().size() == 1);

  histogram.UpdateSpeedFrequency(23.1f); // Frequency should updated to 2
  histogram.UpdateSpeedFrequency(1);
  histogram.UpdateSpeedFrequency(100.1234f);

  REQUIRE(histogram.GetSpeedFrequencies().size() == 3);
  REQUIRE(histogram.GetSpeedFrequencies().at(23.1) == 2);
  REQUIRE(histogram.GetSpeedFrequencies().at(1) == 1);
  REQUIRE(histogram.GetSpeedFrequencies().at(100.1234) == 1);

  histogram.Clear();
  REQUIRE(histogram.GetSpeedFrequencies().size() == 0); // Test Clear function
}

TEST_CASE("Updating multiple histograms with histogram manager") {
  std::vector<idealgas::Particle> particles;

  // 3 small particles with 2 the same speed and 1 unique speed
  particles.emplace_back(idealgas::Particle(5, 1));
  particles.emplace_back(idealgas::Particle(5, 1));
  idealgas::Particle particle(5, 1);
  particle.SetVelocity(glm::vec2(15.1234, 3.12351235)); //Length of this is 15.4
  particles.emplace_back(particle);

  // 3 medium particles of various speeds
  idealgas::Particle particle2(7, 5);
  particle2.SetVelocity(glm::vec2(2, 2));
  particles.emplace_back(particle2);
  particle2.SetVelocity(glm::vec2(6, 7));
  particles.emplace_back(particle2);
  particle2.SetVelocity(glm::vec2(0, 1));
  particles.emplace_back(particle2);

  // 1 Large particle
  idealgas::Particle particle3(10, 5);
  particle3.SetVelocity(glm::vec2(0, 0)); // 0 speed
  particles.emplace_back(particle3);  // 1 large particle

  // Update histogram based on custom particles
  idealgas::HistogramManager manager(glm::vec2(50, 50));
  manager.UpdateHistograms(particles);

  REQUIRE(manager.GetSmallParticleHistogram().GetSpeedFrequencies().size() == 2);
  REQUIRE(manager.GetSmallParticleHistogram().GetSpeedFrequencies().at(2.2) == 2);
  REQUIRE(manager.GetSmallParticleHistogram().GetSpeedFrequencies().at(15.4) == 1);

  REQUIRE(manager.GetMediumParticleHistogram().GetSpeedFrequencies().size() == 3);
  REQUIRE(manager.GetMediumParticleHistogram().GetSpeedFrequencies().at(2.8f) == 1);
  REQUIRE(manager.GetMediumParticleHistogram().GetSpeedFrequencies().at(9.2f) == 1);
  REQUIRE(manager.GetMediumParticleHistogram().GetSpeedFrequencies().at(1) == 1);

  REQUIRE(manager.GetLargeParticleHistogram().GetSpeedFrequencies().size() == 1);
  REQUIRE(manager.GetLargeParticleHistogram().GetSpeedFrequencies().at(0) == 1);
}