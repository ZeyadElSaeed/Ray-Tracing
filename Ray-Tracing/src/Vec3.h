#pragma once
#include <iostream>

class Vec3
{
private:
	double e[3];

public:

	Vec3();
	Vec3(double e0, double e1, double e2);
	virtual ~Vec3() {}

	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }

	Vec3 operator-() const;
	inline double operator[](int i) const { return e[i]; }
	inline double& operator[](int i) { return e[i]; }

	Vec3& operator+=(const Vec3& v);
	Vec3& operator*=(const double t);
	Vec3& operator/=(const double t);

	static Vec3 random();
	static Vec3 random(double min, double max);
	inline double length_squared() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	double length() const;

};

using Point3 = Vec3;

inline std::ostream& operator<< (std::ostream& out, const Vec3& v) {
	return out << v.x() << " " << v.y() << " " << v.z();
}

inline Vec3 operator+(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator+(const Vec3& v , const double value) {
	return Vec3(value + v.x(), value + v.y(), value + v.z());
}

inline Vec3 operator-(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3& u, const Vec3& v) {
	return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(const double t, const Vec3& v) {
	return Vec3(t * v.x(), t * v.y(), t * v.z());
}

inline Vec3 operator*( const Vec3& v, const double t ) {
	return (t * v);
}

inline Vec3 operator/(const Vec3& v, const double t) {
	return (v * (1/t) );
}

inline double dot(const Vec3& u, const Vec3& v) {
	return (u.x() * v.x() + u.y() * v.y() + u.z() * v.z());
}

inline Vec3 cross(const Vec3& u, const Vec3& v) {
	return Vec3(u.y() * v.z() - u.z() * v.y(),
				u.z() * v.x() - u.x() * v.z(),
				u.x() * v.y() - u.y() * v.x() );
}

inline Vec3 unit_vector(Vec3 v) {
	return v / v.length();
}

static Vec3 random_int_unit_sphere() {
	while (true) {
		auto p = Vec3::random(-1, 1);
		if (p.length_squared() < 1)
			return p;
	}
}

static Vec3 random_unit_vector() {
	return unit_vector(random_int_unit_sphere());
}

inline Vec3 random_on_hemisphere(const Vec3& normal) {
	Vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0)
		return on_unit_sphere;
	else
		return - on_unit_sphere;
}