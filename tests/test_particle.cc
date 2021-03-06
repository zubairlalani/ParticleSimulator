#include <catch2/catch.hpp>
#include "core/particle.h"

TEST_CASE("Particle Constructor") {
  idealgas::Particle particle(10, 2);
  REQUIRE(particle.GetRadius() == 10); // reasonable radius
  REQUIRE(particle.GetMass() == 2); // reasonable mass

  REQUIRE_THROWS_AS(idealgas::Particle(0, 3), std::invalid_argument); // invalid radius
  REQUIRE_THROWS_AS(idealgas::Particle(4, 0), std::invalid_argument); // invalid mass
  REQUIRE_THROWS_AS(idealgas::Particle(4, -1), std::invalid_argument); // invalid mass
  REQUIRE_THROWS_AS(idealgas::Particle(0, 0), std::invalid_argument); // invalid mass and radius
}

TEST_CASE("Update position") {
  idealgas::Particle particle(10, 3);
  // Make sure initial position and initial velocity is correct
  REQUIRE(particle.GetPosition() == glm::vec2(60, 60)); // (60, 60) is the spawn pt of all particles
  REQUIRE(particle.GetVelocity() == glm::vec2(2, 1)); // initial vel is <2,1> for all particles

  //Confirm position is updated
  particle.UpdatePosition();
  REQUIRE(particle.GetPosition() == glm::vec2(62, 61));
}

TEST_CASE("Determining whether there is a collision between two particles works") {
  SECTION("Same sized particles") {
    idealgas::Particle particle(10, 5);
    idealgas::Particle particle2(10, 7);

    SECTION("Exactly 2 radius distance away in x direction") {
      particle2.SetPosition(glm::vec2(80, 60));
      particle2.SetVelocity(glm::vec2(-2, 1));  // Makes sure particles are going towards each other
      REQUIRE(particle.IsParticleCollision(particle2)); // To the right

      particle2.SetPosition(glm::vec2(40, 60));
      particle2.SetVelocity(glm::vec2(3, 1));
      REQUIRE(particle.IsParticleCollision(particle2)); // To the left

    }

    SECTION("Less than 2 radius distance away in x direction") {
      particle2.SetPosition(glm::vec2(70, 60)); // Right of first particle
      particle2.SetVelocity(glm::vec2(-2, 1));
      REQUIRE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(50, 60)); // Left of first particle
      particle2.SetVelocity(glm::vec2(3, 1));
      REQUIRE(particle.IsParticleCollision(particle2));

    }

    SECTION("Exactly 2 radius distance away in y direction"){
      particle2.SetPosition(glm::vec2(60, 80)); // Below the first particle
      particle2.SetVelocity(glm::vec2(2, -1));
      REQUIRE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(60, 40)); // Above first particle
      particle2.SetVelocity(glm::vec2(2, 2));
      REQUIRE(particle.IsParticleCollision(particle2));
    }

    SECTION("Less than 2 radius distance in y direction") {
      particle2.SetPosition(glm::vec2(60, 70)); // Below the first particle
      particle2.SetVelocity(glm::vec2(2, -1));
      REQUIRE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(60, 50)); // Above first particle
      particle2.SetVelocity(glm::vec2(2, 2));
      REQUIRE(particle.IsParticleCollision(particle2));
    }

    SECTION("Greater than 2 radius distance away from each other") {
      particle2.SetPosition(glm::vec2(81, 70));
      particle2.SetVelocity(glm::vec2(-2, 1));
      REQUIRE_FALSE(particle.IsParticleCollision(particle2));
    }

    SECTION("Within collision range but not moving towards each other") {
      particle2.SetPosition(glm::vec2(60, 80));
      REQUIRE_FALSE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(50, 50));
      particle2.SetVelocity(glm::vec2(-2, 1));
      REQUIRE_FALSE(particle.IsParticleCollision(particle2));

      particle2.SetVelocity(glm::vec2(0, 1));
      REQUIRE_FALSE(particle.IsParticleCollision(particle2));

      particle2.SetVelocity(glm::vec2(2, 1));
      REQUIRE_FALSE(particle.IsParticleCollision(particle2));
    }
  }

  SECTION("Different sized particles (different radii)") {
    idealgas::Particle particle(10, 5);
    idealgas::Particle particle2(15, 7);

    SECTION("Exactly 2 radius distance away in x direction") {
      particle2.SetPosition(glm::vec2(85, 60));
      particle2.SetVelocity(glm::vec2(-2, 1));  // Makes sure particles are going towards each other
      REQUIRE(particle.IsParticleCollision(particle2)); // To the right

      particle2.SetPosition(glm::vec2(35, 60));
      particle2.SetVelocity(glm::vec2(3, 1));
      REQUIRE(particle.IsParticleCollision(particle2)); // To the left
    }

    SECTION("Less than 2 radius distance away in x direction") {
      particle2.SetPosition(glm::vec2(80, 60)); // Right of first particle
      particle2.SetVelocity(glm::vec2(-2, 1));
      REQUIRE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(50, 60)); // Left of first particle
      particle2.SetVelocity(glm::vec2(3, 1));
      REQUIRE(particle.IsParticleCollision(particle2));

    }

    SECTION("Exactly 2 radius distance away in y direction"){
      particle2.SetPosition(glm::vec2(60, 85)); // Below the first particle
      particle2.SetVelocity(glm::vec2(2, -1));
      REQUIRE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(60, 35)); // Above first particle
      particle2.SetVelocity(glm::vec2(2, 2));
      REQUIRE(particle.IsParticleCollision(particle2));
    }

    SECTION("Less than 2 radius distance in y direction") {
      particle2.SetPosition(glm::vec2(60, 80)); // Below the first particle
      particle2.SetVelocity(glm::vec2(2, -1));
      REQUIRE(particle.IsParticleCollision(particle2));

      particle2.SetPosition(glm::vec2(60, 40)); // Above first particle
      particle2.SetVelocity(glm::vec2(2, 2));
      REQUIRE(particle.IsParticleCollision(particle2));
    }

    SECTION("Greater than 2 radius distance away from each other") {
      particle2.SetPosition(glm::vec2(86, 70));
      particle2.SetVelocity(glm::vec2(-2, 1));
      REQUIRE_FALSE(particle.IsParticleCollision(particle2));
    }

    SECTION("Extremely Large difference in radii") {
      idealgas::Particle particle3(1, 5);
      idealgas::Particle particle4(70, 7); // Very Large difference in radii
      particle4.SetPosition(glm::vec2(60+71, 60));
      particle4.SetVelocity(glm::vec2(-2, 1));  // Makes sure particles are going towards each other
      REQUIRE(particle3.IsParticleCollision(particle4));

      particle4.SetPosition(glm::vec2(60+72, 60));
      REQUIRE_FALSE(particle3.IsParticleCollision(particle4));


      idealgas::Particle particle5(2, 7); // Very Small difference in radii
      particle5.SetPosition(glm::vec2(60+3, 60));
      particle5.SetVelocity(glm::vec2(-2, 1));  // Makes sure particles are going towards each other
      REQUIRE(particle3.IsParticleCollision(particle5));

      particle5.SetPosition(glm::vec2(60+4, 60));
      REQUIRE_FALSE(particle3.IsParticleCollision(particle5));
    }
  }
}

TEST_CASE("Velocities after particle collision") {
  SECTION("Horizontal collision") {
    SECTION("Same Mass") {
      idealgas::Particle particle(10, 5);
      idealgas::Particle particle2(10, 5);
      particle2.SetPosition(glm::vec2(80, 60));
      particle2.SetVelocity(glm::vec2(
          -2, 1));  // Makes sure particles are going towards each other
      glm::vec2 result_vel = particle.CalculateVelocity(particle2);
      glm::vec2 result_vel2 = particle2.CalculateVelocity(particle);

      REQUIRE(result_vel == glm::vec2(-2, 1));  // calculated by hand
      REQUIRE(result_vel2 == glm::vec2(2, 1));
    }

    SECTION("Different Mass") {
      idealgas::Particle particle(10, 5);
      idealgas::Particle particle2(15, 10);
      particle2.SetPosition(glm::vec2(80, 60));
      particle2.SetVelocity(glm::vec2(
          -2, 1));  // Makes sure particles are going towards each other
      glm::vec2 result_vel = particle.CalculateVelocity(particle2);
      glm::vec2 result_vel2 = particle2.CalculateVelocity(particle);

      glm::vec2 test = result_vel - glm::vec2(-3.333f, 1); // calculated by hand
      REQUIRE(fabs(test.x) < .001f);
      REQUIRE(fabs(test.y) < .001f);

      test = result_vel2 - glm::vec2(0.6666f, 1);
      REQUIRE(fabs(test.x) < .001f);
      REQUIRE(fabs(test.y) < .001f);
    }
  }

  SECTION("Diagonal collision") {
    SECTION("Same Mass") {
      idealgas::Particle particle(1, 5);
      idealgas::Particle particle2(1, 5);
      particle.SetPosition(glm::vec2(20, 20));
      particle.SetVelocity(glm::vec2(0.1, 0));
      particle2.SetPosition(glm::vec2(21.4, 21.4));
      particle2.SetVelocity(glm::vec2(-0.1, 0));

      glm::vec2 result_vel = particle.CalculateVelocity(particle2);
      glm::vec2 test = result_vel - glm::vec2(0.0f, -.1f);
      REQUIRE(fabs(test.x) < .00001f);
      REQUIRE(fabs(test.y) < .00001f);

      glm::vec2 result_vel2 = particle2.CalculateVelocity(particle);
      glm::vec2 test2 = result_vel2 - glm::vec2(0.0f, .1f);
      REQUIRE(fabs(test2.x) < .00001f);
      REQUIRE(fabs(test2.y) < .00001f);
    }

    SECTION("Different Mass") {
      idealgas::Particle particle(1, 6);
      idealgas::Particle particle2(1, 2);
      particle.SetPosition(glm::vec2(20, 20));
      particle.SetVelocity(glm::vec2(0.1, 0));
      particle2.SetPosition(glm::vec2(21.4, 21.4));
      particle2.SetVelocity(glm::vec2(-0.1, 0));

      glm::vec2 result_vel = particle.CalculateVelocity(particle2);
      glm::vec2 test = result_vel - glm::vec2(0.05f, -.05f);
      REQUIRE(fabs(test.x) < .00001f);
      REQUIRE(fabs(test.y) < .00001f);


      glm::vec2 result_vel2 = particle2.CalculateVelocity(particle);
      glm::vec2 test2 = result_vel2 - glm::vec2(0.0500f, .1500f);
      REQUIRE(fabs(test2.x) < .0001f);
      REQUIRE(fabs(test2.y) < .0001f);
    }
  }
}

TEST_CASE("Velocities after wall collision") {
  idealgas::Particle particle(5, 1);
  SECTION("Right wall") {
    //Particle in range of right wall and moving towards right wall
    particle.SetPosition(glm::vec2(445, 355));
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() == glm::vec2(-2, 1));

    //Particle in range of right wall and moving away from right wall
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() != glm::vec2(2, 1)); // Shouldn't switch it back
  }

  SECTION("Left Wall") {
    //In range of left wall and moving towards left wall
    particle.SetPosition(glm::vec2(55, 200));
    particle.SetVelocity(glm::vec2(-2, 1));
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() == glm::vec2(2, 1));

    //In range of left wall and moving away from left wall
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() != glm::vec2(-2, 1));
  }

  SECTION("Top wall") {
    //In range of top wall and moving towards top wall
    particle.SetPosition(glm::vec2(70, 55));
    particle.SetVelocity(glm::vec2(2, -1));
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() == glm::vec2(2, 1));

    //In range of top wall and moving away from top wall
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() != glm::vec2(2, -1));
  }

  SECTION("Bottom Wall") {
    //In range of bottom wall and moving towards bottom wall
    particle.SetPosition(glm::vec2(300, 445));
    particle.SetVelocity(glm::vec2(5, 1));
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() == glm::vec2(5, -1));

    //In range of bottom wall and moving away from bottom wall
    particle.CalculateWallCollisionVelocity(400, 50);
    REQUIRE(particle.GetVelocity() != glm::vec2(5, 1));
  }
}


