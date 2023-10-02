#pragma once

#include <cmath>
#include <limits>
#include <memory>
// #include <cstdlib>

// Using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utilities Function
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	// return a random number in [0, 1)
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	// return a random number between [min, max)
	return min + (max - min) * random_double();
}

// Common Header
#include "interval.h"
#include "ray.h"
#include "vec3.h"
