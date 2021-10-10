//
// Created by Aeomanate on 06.08.2021.
//

#ifndef LODE_RUNNER_RAND_HPP
#define LODE_RUNNER_RAND_HPP

#include <random>
#include <chrono>
#include "Coord.hpp"

int randInt(int a, int b);


inline Coord randIntXCoord(int a, int b) {
    return Coord { randInt(a, b), 0 };
}

#endif // LODE_RUNNER_RAND_HPP
