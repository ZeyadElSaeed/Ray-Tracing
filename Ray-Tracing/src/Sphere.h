#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(Point3 center, double radius);
	bool hit(const Ray& ray, double ray_t_min, double ray_t_max, HitRecord& record) const;
private:
	Point3 m_Center;
	double m_Radius;
};