#pragma once

#include "Vec3.h"

using Color = Vec3;

void write_color(std::ostream& out, Color pixel_color) {
	out << static_cast<int>(pixel_color.x() * 255.99) << " "
		<< static_cast<int>(pixel_color.y() * 255.99) << " "
		<< static_cast<int>(pixel_color.z() * 255.99) << "\n";
}