#pragma once
#include <iostream>

class Vec3
{
private:
	double e[3];

public:
	Vec3(double e0 = 0.0, double e1 = 0.0, double e2 = 0.0)
		: e{ e0, e1, e2 }
	{}
	virtual ~Vec3() {}

	inline double x() const { return e[0]; }
	inline double y() const { return e[1]; }
	inline double z() const { return e[2]; }

	Vec3 operator-()const
	{
		return Vec3(-e[0], -e[1], -e[2]);
	}

	inline double operator[](int i) const { return e[i]; }
	inline double& operator[](int i) { return e[i]; }

	Vec3& operator+=(const Vec3& v) {
		e[0] += v[0];
		e[1] += v[1];
		e[2] += v[2];
		return *this;
	}
	Vec3& operator*=(const double t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}
	Vec3& operator/=(const double t) {
		return (*this *= (1 / t));
	}

	static Vec3 random() {
		return Vec3(random_double(), random_double(), random_double());
	}
	static Vec3 random(double min, double max) {
		return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
	inline double length_squared() const { return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }

	double length() const {
		return sqrt(length_squared());
	}

	bool nearZero() {
		auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}
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

inline Vec3 unit_vector(const Vec3 v)  {
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

inline Vec3 reflect(const Vec3& ray, const Vec3& normal) {
	return ray - (2 * dot(ray, normal)*normal);
}