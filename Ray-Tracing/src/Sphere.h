#pragma once
#include "Hittable.h"

class Sphere : public Hittable
{
public:
	Sphere(Point3 center, double radius, shared_ptr<Material> material)
		: m_Center(center), m_Radius(radius), m_Material(material)
	{
	}
	bool hit(const Ray& ray, Interval ray_t, HitRecord& record) const override
	{
		// finding the points of intersection by solving the sphere equation and ray equation together
		Vec3 oc = ray.origin() - m_Center;
		auto a = ray.direction().length_squared();
		auto half_b = dot(ray.direction(), oc);
		auto c = oc.length_squared() - (m_Radius * m_Radius);
		auto discriminant = (half_b * half_b) - (a * c);

		if (discriminant < 0)
			return false;

		// Find the nearest root that intersect with ray
		auto sqrtDisc = sqrt(discriminant);
		auto root = (-half_b - sqrtDisc) / a;
		if (!ray_t.surrounds(root))
		{
			root = (-half_b + sqrtDisc) / a;
			if (!ray_t.surrounds(root))
			{
				return false;
			}
		}
		record.m_T = root;
		record.m_Point = ray.at(record.m_T);
		Vec3 outward_normal = (record.m_Point - m_Center) / m_Radius;
		record.setFaceNormal(ray, outward_normal);
		record.m_Material = m_Material;

		return true;
	}
private:
	Point3 m_Center;
	double m_Radius;
	shared_ptr<Material> m_Material;
};