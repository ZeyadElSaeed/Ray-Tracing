#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(Point3 center, double radius);
	bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const;
private:
	Point3 m_Center;
	double m_Radius;
};