#ifndef UTILITIES_H
#define UTILITIES_H
#include <cmath>
#include <random>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const float infinity = std::numeric_limits<double>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline float random_float() {
    thread_local std::mt19937 gen{std::random_device{}()};
    thread_local std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(gen);
}

inline double random_float(float min, float max) {
    // Returns a random float in [min,max).
    return min + (max-min)*random_float();
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif