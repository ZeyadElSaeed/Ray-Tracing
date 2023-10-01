#include "Sphere.h"

Sphere::Sphere(Point3 center, double radius)
	: m_Center(center), m_Radius(radius)
{}
bool Sphere::hit(const Ray& ray, Interval ray_t, HitRecord& record) const
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
	if ( !ray_t.surrounds(root))
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
		
    return true;
}