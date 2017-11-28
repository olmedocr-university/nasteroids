#include <cmath>
#include <iostream>
#include "Computations.h"
#include "Constants.h"
#include "omp.h"

/**
 * Returns the distance between the @param a and @param b
 * @param a body object
 * @param b body object
 * @return distance
 */
double computeDistance(Asteroid a, Body b) {
    return sqrt(pow((a.getPosX() - b.getPosX()), 2) + pow((a.getPosY() - b.getPosY()), 2));
}

/**
 * Returns the angle of influence between @param a and @param b
 * @param a
 * @param b
 * @return angle of influence
 */
double computeAngleOfInfluence(Asteroid a, Body b) {
    double slope = (a.getPosY() - b.getPosY()) / (a.getPosX() - b.getPosX());
    if (std::isinf(slope)) {
        return atan(slope);
    }
    if (slope < -1 || slope > 1) {
        slope = slope - trunc(slope);
    }
    return atan(slope);

}

/**
 * TODO:
 * @param a
 * @param b
 * @return vector with the two components of the force with [0] being the x axis and [1] being the y axis
 */
std::vector<double> computeAttractionForce(Asteroid a, Body b) {
    double distance = computeDistance(a, b);
    double alfa = computeAngleOfInfluence(a, b);

    std::vector<double> forces(2);

    forces[0] = ((GRAVITY * a.getMass() * b.getMass()) / pow(distance, 2)) * cos(alfa);
    forces[1] = ((GRAVITY * a.getMass() * b.getMass()) / pow(distance, 2)) * sin(alfa);

    if (forces[0] > MAXIMUM_FORCE) {
        forces[0] = MAXIMUM_FORCE;
    }
    if (forces[1] > MAXIMUM_FORCE) {
        forces[1] = MAXIMUM_FORCE;
    }

    return forces;
}

/**
 * Applies the rebound effect to the @param a once checked if necessary
 * @param a
 */
void computeReboundEffect(Asteroid &a) {
    double posX = a.getPosX();
    double posY = a.getPosY();
//#pragma omp parallel sections
    {
//#pragma omp section
        {
            if (posX <= 0) {
                a.setPosX(2);
                a.setVelocityX(a.getVelocityX() * -1);
            }
        }
//#pragma omp section
        {
            if (posX >= SPACE_WIDTH) {
                a.setPosX(SPACE_WIDTH - 2);
                a.setVelocityX(a.getVelocityX() * -1);
            }
        }
//#pragma omp section
        {
            if (posY <= 0) {
                a.setPosY(2);
                a.setVelocityX(a.getVelocityY() * -1);
            }
        }
//#pragma omp section
        {
            if (posY >= SPACE_HEIGHT) {
                a.setPosY(SPACE_HEIGHT - 2);
                a.setVelocityX(a.getVelocityY() * -1);
            }
        }
    }
}

/**
 * Computes the position of the @param a regarding the vector with the Asteroids @param asteroids and
 * the vector with the Planets @param planets
 * @param a
 * @param asteroids
 * @param planets
 */
void computePosition(Asteroid &a) {
    a.setPosX(a.getPosX() + a.getVelocityX() * TIME_INTERVAL);
    a.setPosY(a.getPosY() + a.getVelocityY() * TIME_INTERVAL);
}

/**
 * TODO:
 * @param a
 * @param asteroids
 * @param planets
 */
void computeVelocity(Asteroid &a, std::vector<double> accelerations) {
    a.setVelocityX(a.getVelocityX() + accelerations[0] * TIME_INTERVAL);
    a.setVelocityY(a.getVelocityY() + accelerations[1] * TIME_INTERVAL);
}

/**
 * TODO:
 * @param a
 * @param asteroids
 * @param planets
 * @return vector with the two components of the acceleration with [0] being the x axis and [1] being the y axis
 */
double computeAcceleration(Asteroid a, double force) {
    return force / a.getMass();
}
