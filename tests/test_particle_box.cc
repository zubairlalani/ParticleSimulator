#include <catch2/catch.hpp>
#include "visualizer/particle_box.h"

TEST_CASE("Add particles and clear particles") {
  idealgas::ParticleBox particleBox(glm::vec2(50, 50), 400, 400);
  particleBox.AddParticle();
  REQUIRE(particleBox.GetParticles()[0].GetPosition() == idealgas::Particle(10).GetPosition());
  REQUIRE(particleBox.GetParticles().size() == 1);

  particleBox.AddParticle();
  REQUIRE(particleBox.GetParticles()[0].GetPosition() == idealgas::Particle(10).GetPosition());
  REQUIRE(particleBox.GetParticles()[1].GetPosition() == idealgas::Particle(10).GetPosition());
  REQUIRE(particleBox.GetParticles().size() == 2);

  particleBox.Clear();
  REQUIRE(particleBox.GetParticles().size() == 0);

  // Make sure that calling clear on already empty list doesn't cause problems
  particleBox.Clear();
  REQUIRE(particleBox.GetParticles().size() == 0);
}

TEST_CASE("Updating particle variables each frame works") {
  idealgas::ParticleBox particleBox(glm::vec2(50, 50), 400, 400);
  particleBox.UpdateParticles(50); // Calling update when there's no particles shouldn't crash program

  SECTION("Particles correctly move according to velocity") {
    particleBox.AddParticle();
    particleBox.UpdateParticles(50);  // only one particle test
    // Initial pos is (60, 60) and initial vel is (2,1) so should go to (62,61)
    REQUIRE(particleBox.GetParticles()[0].GetPosition() == glm::vec2(62, 61));
    particleBox.AddParticle();

    for (size_t i = 0; i < 3; i++) {
      particleBox.UpdateParticles(50);  // Move the two particles many times
      particleBox.UpdateParticles(50);
      particleBox.UpdateParticles(50);
      particleBox.UpdateParticles(50);
    }

    // 5 particles over all
    REQUIRE(particleBox.GetParticles()[0].GetPosition() == glm::vec2(86, 73));
    REQUIRE(particleBox.GetParticles()[1].GetPosition() == glm::vec2(84, 72));
  }

  SECTION("Wall collision") {
    particleBox.AddParticle();
    // Need 192 frames for a particle to reach right wall
    for(size_t i = 0; i < 193; i++){
      particleBox.UpdateParticles(50);
    }
    REQUIRE(particleBox.GetParticles()[0].GetVelocity() == glm::vec2(-2, 1));

    // More wall collision tests and particle collision tests in particle class
  }
}

TEST_CASE("Changing speeds of particles") {
  idealgas::ParticleBox particleBox(glm::vec2(50, 50), 400, 400);
  particleBox.AddParticle();
  particleBox.UpdateParticles(50); // Create a particle and run two frames
  particleBox.UpdateParticles(50);

  particleBox.AddParticle();

  SECTION("Speeding up particles") {
    for (size_t i = 0; i < 3; i++) {
      particleBox.UpdateParticles(50);  // Run a couple of frames of the simulation
      particleBox.UpdateParticles(50);
      particleBox.UpdateParticles(50);
      particleBox.UpdateParticles(50);
    }

    particleBox.IncreaseDecreaseSpeed(1);
    glm::vec2 test = particleBox.GetParticles()[0].GetVelocity() - glm::vec2(3.0f, 2.0f);
    REQUIRE(fabs(test.x) < .00001f);
    REQUIRE(fabs(test.y) < .00001f);

    test = particleBox.GetParticles()[1].GetVelocity() - glm::vec2(3.0f, 2.0f);
    REQUIRE(fabs(test.x) < .00001f);
    REQUIRE(fabs(test.y) < .00001f);
  }

  SECTION("Slow down particles") {
    for (size_t i = 0; i < 3; i++) {
      particleBox.UpdateParticles(50);  // Run a couple of frames of the simulation
      particleBox.UpdateParticles(50);
      particleBox.UpdateParticles(50);
      particleBox.UpdateParticles(50);
    }

    particleBox.IncreaseDecreaseSpeed(-1);

    glm::vec2 test = particleBox.GetParticles()[0].GetVelocity() - glm::vec2(1, 0);
    REQUIRE(fabs(test.x) < .00001f);
    REQUIRE(fabs(test.y) < .00001f);

    test = particleBox.GetParticles()[1].GetVelocity() - glm::vec2(1.0f, 0.0f);
    REQUIRE(fabs(test.x) < .00001f);
    REQUIRE(fabs(test.y) < .00001f);
  }
}
