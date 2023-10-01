#pragma once
#include "Ray.h"
struct HitRecord
{
	Point3 m_Point;
	Vec3 m_Normal;
	double m_T;
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& ray, double ray_t_min, double ray_t_max, HitRecord& record) const = 0;

};