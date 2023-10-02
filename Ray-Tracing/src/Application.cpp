#include <iostream>
#include "rtweekend.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

int main() {
	// World
	HittableList world;
	world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1), 0.5));
	world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1), 100));

	Camera camera( 16.0/9.0, 800, 5, 50);
	camera.Render(world);
	
	return 0;
}