#pragma once
#include "rtweekend.h"
#include "Hittable.h"
#include "Color.h"
#include <iostream>
#include <fstream>

class Camera
{
public:
	Camera(double aspect_ratio, int image_width, int samples_per_pixel = 10, int max_rays_bounces = 10)
		:m_Aspect_ratio(aspect_ratio) , m_Image_width(image_width), m_Samples_per_pixel(samples_per_pixel), m_Max_rays_bounces(max_rays_bounces)
	{
		Intialize();
	}

	void Render(Hittable& world)
	{
		//Config the file to be written
		std::ofstream outputFile;
		outputFile.open("test.ppm");
		if (!outputFile.is_open()) {
			std::cerr << "Failed to open the file for writing!" << std::endl;
		}
		// Render
		std::cout << " Start Rendering " << std::endl;
		outputFile << "P3\n" << m_Image_width << " " << m_Image_height << "\n255\n";
		for (int j = 0; j < m_Image_height; j++) {
			std::clog << "\rScanLines Remaining " << (m_Image_height - j) << " " << std::flush;
			for (int i = 0; i < m_Image_width; i++) {
				Color pixel_color(0, 0, 0);
				for (int sample = 0; sample < m_Samples_per_pixel; sample++) {
					Ray ray = get_ray(i, j);
					pixel_color += ray_color(ray, world, m_Max_rays_bounces);
				}
				write_color(outputFile, pixel_color, m_Samples_per_pixel);
			}
		}
		outputFile.close();
		if (outputFile.fail()) {
			std::cerr << "Failed to close the file!" << std::endl;
		}
		std::cout << "File write successful!" << std::endl;
		std::clog << "\rDone.                 \n";
	}
private:
	Ray get_ray(int i, int j) const {
		auto pixel_center = m_Pixel00_location + (i * m_Pixel_delta_u) + (j * m_Pixel_delta_v);
		auto pixel_sample = pixel_center + pixel_sample_square();
		return Ray(m_Center, pixel_sample - m_Center );
	}

	Vec3 pixel_sample_square() const
	{
		// sample from -0.5 to 0.5
		auto px = -0.5 + random_double();
		auto py = -0.5 + random_double();
		return ((px * m_Pixel_delta_u) + (py * m_Pixel_delta_v));
	}


	Color ray_color(const Ray& ray, const Hittable& world, int max_rays_bounces)
	{
		if (max_rays_bounces < 1)
			return Color(0, 0, 0);

		HitRecord record;
		if (world.hit(ray, Interval(0.001, infinity), record)) {
			// Keep reflect lights untill they don't hit surface (rest of function)
			Vec3 direction = record.m_Normal + random_unit_vector();
			Ray r(record.m_Point, direction);
			return 0.5 * ray_color( r, world, max_rays_bounces-1) ;
		}

		Vec3 unit_direction = unit_vector(ray.direction());
		auto a = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
	}

	void Intialize()
	{
		m_Center = Point3(0, 0, 0);
		m_Image_height = static_cast<int>(m_Image_width / m_Aspect_ratio);
		m_Image_height = (m_Image_height > 1) ? m_Image_height : 1;
		auto focal_length = 1.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * (static_cast<double>(m_Image_width) / m_Image_height);
		auto viewport_u = Vec3(viewport_width, 0, 0);
		auto viewport_v = Vec3(0, -viewport_height, 0);
		m_Pixel_delta_u = viewport_u / m_Image_width;
		m_Pixel_delta_v = viewport_v / m_Image_height;
		auto viewport_upper_left = m_Center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; // where is upper_left to camera_position
		m_Pixel00_location = viewport_upper_left + 0.5 * (m_Pixel_delta_u + m_Pixel_delta_v); // to get the center of the square pixel
	}

private:
	double m_Aspect_ratio;
	int    m_Image_width;
	int m_Image_height;
	Point3 m_Center;
	Vec3 m_Pixel_delta_u;
	Vec3 m_Pixel_delta_v;
	Point3 m_Pixel00_location;
	int    m_Samples_per_pixel;
	int    m_Max_rays_bounces;
};