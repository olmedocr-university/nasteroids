#ifndef NASTEROIDS_COMPUTATIONS_H
#define NASTEROIDS_COMPUTATIONS_H

#include "Body.h"
#include "Asteroid.h"

class Computations {

public:

    double computeDistance(Body a, Body b);

    double computeAngleOfInfluence(Body a, Body b);

    double computeAttractionForce(Body a, Body b);

    void computeReboundEffect(Asteroid a);
};

#endif //NASTEROIDS_COMPUTATIONS_H
