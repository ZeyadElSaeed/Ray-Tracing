#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Color.h"
#include "Ray.h"
#include "Sphere.h"



Color ray_color(const Ray& ray) {
	Sphere sphere( Point3(0, 0, -1), 0.5 );
	HitRecord record;
	if (sphere.hit(ray, -1, 100, record)) {
		return 0.5 * (Color(record.m_Normal.x(), record.m_Normal.y(), record.m_Normal.z()) + 1);
	}
	
	Vec3 unit_direction = unit_vector(ray.direction());
	// Normalize the vector is form [-1, 1]
	auto a = 0.5 * (unit_direction.y() + 1.0); // a is [0, 1]
	// linear blinding: (1-a)*StartValue + (a)*EndValue
	return (1.0-a)*Color(1.0,1.0,1.0) + a*Color(0.5, 0.7, 1.0);
}

int main() {
	//Config the file to be written
	std::ofstream outputFile;
	outputFile.open("test.ppm");
	if (!outputFile.is_open()) {
		std::cerr << "Failed to open the file for writing!" << std::endl;
		return 1; // Exit with an error code
	}

	// Image 
	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = static_cast<int>( image_width / aspect_ratio ) ;
	image_height = (image_height > 1) ? image_height : 1;	

	// Camera
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	// we use the actual ratio not the ideal one (16/9) 
	auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
	auto camer_center = Point3(0, 0, 0);

	// Calculate the vectors across the horizontal and down the vertical viewport edges.
	auto viewport_u = Vec3(viewport_width, 0, 0); // horizontal viewport vector
	auto viewport_v = Vec3(0, -viewport_height, 0); // vertical viewport vector to down

	// Calculate the horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// Calculate the location of the upper left pixel.
	auto viewport_upper_left = camer_center - Vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; // where is upper_left to camera_position
	auto pixel00_location = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // to get the center of the square pixel

	// Render
	outputFile << "P3\n" << image_width << " " << image_height << "\n255\n";
	for (int j = 0; j < image_height; j++) {
		std::clog << "\rScanLines Remaining " << (image_height - j) << " " << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto pixel_center = pixel00_location + (i * pixel_delta_u) + (j * pixel_delta_v);
			auto ray_direction = pixel_center - camer_center;
			Ray ray(camer_center, ray_direction);
			Color pixel_color = ray_color(ray);
			write_color(outputFile, pixel_color);
		}
	}
	outputFile.close();
	if (outputFile.fail()) {
		std::cerr << "Failed to close the file!" << std::endl;
		return 1; // Exit with an error code
	}
	std::cout << "File write successful!" << std::endl;
	std::clog << "\rDone.                 \n";
	return 0;
}