#include "rtweekend.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Color.h"
#include "Material.h"

int main() {
	// World
	HittableList world;

	auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
	auto material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
	auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);


	world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));


	Camera camera( 16.0/9.0, 800, 100, 500);
	camera.Render(world);
	
	return 0;
}