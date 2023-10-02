#pragma once
#include "rtweekend.h"

class Material;

struct HitRecord
{
	Point3 m_Point;
	Vec3 m_Normal;
	double m_T;
	bool m_FrontFace;
	shared_ptr<Material>m_Material;

	void setFaceNormal(const Ray& ray, const Vec3& outward_normal) {
		m_FrontFace = dot(ray.direction(), outward_normal) < 0;
		m_Normal = m_FrontFace ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const = 0;

};