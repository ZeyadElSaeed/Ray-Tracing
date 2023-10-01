#pragma once

#include <cmath>
#include <limits>
#include <memory>

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

// Common Header
#include "Ray.h"
#include "Vec3.h"
#include "Interval.h"
