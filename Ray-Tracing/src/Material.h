#pragma once
#include "rtweekend.h"
#include "Color.h"

struct HitRecord;

class Material {
public:
	virtual ~Material() = default;

	virtual bool scatter(const Ray &rayIn, const HitRecord &record, Color & attenuation, Ray &scattered )const  = 0;
};



class Lambertian : public Material
{
public :
	Lambertian(const Color &albedo)
		:m_Albedo(albedo)
	{}

	bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override
	{
		Vec3 scatterDirection = record.m_Normal + random_unit_vector();
		scattered = Ray(record.m_Point, scatterDirection);

		if (scatterDirection.nearZero())
		{
			// In case normal and unit vector are in opposite direction then their total is 0
			scatterDirection = record.m_Normal;
		}
		attenuation = m_Albedo;
		return true;
	}

private:
	Color m_Albedo;
};


class Metal : public Material
{
public:
	Metal(const Color& albedo, const double fuzz)
		:m_Albedo(albedo), m_Fuzz(fuzz < 1? fuzz: 0)
	{}

	bool scatter(const Ray& rayIn, const HitRecord& record, Color& attenuation, Ray& scattered) const override
	{
		Vec3 rayDirection = unit_vector(rayIn.direction());
		Vec3 reflected = reflect(rayDirection, record.m_Normal );
		scattered = Ray(record.m_Point, reflected + m_Fuzz*random_unit_vector());
		attenuation = m_Albedo;
		return (dot(scattered.direction(), record.m_Normal) > 0);;
	}

private:
	Color m_Albedo;
	double m_Fuzz;
};