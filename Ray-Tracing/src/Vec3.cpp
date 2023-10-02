#include "rtweekend.h"

Vec3::Vec3()
	:e{0.0, 0.0, 0.0}
{
}

Vec3::Vec3(double e0, double e1, double e2)
	: e{ e0, e1, e2 }
{
}

Vec3 Vec3::operator-() const
{ 
	return Vec3(-e[0], -e[1], -e[2]);
}

Vec3& Vec3::operator+=(const Vec3& v){
	e[0] += v[0];
	e[1] += v[1];
	e[2] += v[2];
	return *this;
}
Vec3& Vec3::operator*=(const double t){
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}
Vec3& Vec3::operator/=(const double t){
	return (*this *= (1/t));
}

Vec3 Vec3::random() {
	return Vec3(random_double(), random_double(), random_double());
}
Vec3 Vec3::random(double min, double max) {
	return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

double Vec3::length() const {
	return sqrt(length_squared());
}
