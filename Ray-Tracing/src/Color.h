#pragma once

#include "Vec3.h"

using Color = Vec3;

inline double linear_to_gamma(double linear_component, double gamma)
{
	return pow(linear_component, 1.0 / gamma);
}
void write_color(std::ostream& out, Color pixel_color, int samples_per_pixels) {
	double gamma = 2.0;

	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	auto scale = 1.0 / samples_per_pixels;
	r *= scale;
	g *= scale;
	b *= scale;

	r = linear_to_gamma(r, gamma);
	g = linear_to_gamma(g, gamma);
	b = linear_to_gamma(b, gamma);

	static const Interval intensity(0, 0.9999);
	r = intensity.clamp(r);
	g = intensity.clamp(g);
	b = intensity.clamp(b);
	out << static_cast<int>(r * 255.99) << " "
		<< static_cast<int>(g * 255.99) << " "
		<< static_cast<int>(b * 255.99) << "\n";
}