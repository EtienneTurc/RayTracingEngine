#include <iostream>
#include <string>
#include "image.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "light/light_point.hpp"
#include "object/plan.hpp"

int main(int argc, char const *argv[])
{
	std::cout << "Ray tracer starting\n";

	//Description of the scene
	Camera cam;
	Scene scene(cam);

	Light_point lgt(Point3d(1, 1, 1), 255, 255, 0);
	Plan plan(Vector3d(0, 0, 1), 0);

	scene.addLigth(lgt);
	scene.addObject<Plan>(plan);

	Image img(100, 100, 3);

	//Render

	//Save
	img.save("test_save.ppm");
	return 0;
}
