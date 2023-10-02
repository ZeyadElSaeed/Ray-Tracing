#pragma once
#include "Vec3.h"

class Ray {
public:
	Ray(const Point3& origin = Point3(0,0,0), const Vec3& direction = Vec3(1,1,1))
		: m_Origin(origin), m_Direction(direction)
		{
		}

	inline Point3 origin() const  { return m_Origin; }
	inline Vec3 direction() const { return m_Direction; }

	Point3 at(double t) const {
		return m_Origin + (t * m_Direction);
	}

private:
	Point3 m_Origin;
	Vec3 m_Direction;
};