#include "engine/basic_engine.hpp"
#include "utils/vector3d.hpp"
#include "utils/point3d.hpp"
#include "object/object.hpp"
#include "params.hpp"

float BasicEngine::minDistanceToObject(const Point3d pt, const Vector3d ray)
{
	std::vector<Object> objects = scene.getObjects();
	int size = objects.size();
	if (!size)
		return -1;

	float min = objects[0].distance(pt, ray);
	for (int i = 1; i < objects.size(); i++)
	{
		float tmp = objects[i].distance(pt, ray);
		if (tmp < min)
			min = tmp;
	}

	return min;
}

color_rgb BasicEngine::trace(const Point3d pt, const Vector3d ray)
{
	std::vector<Object> objects = scene.getObjects();

	float dist = minDistanceToObject(pt, ray);
	Vector3d r(ray);
	r = r * dist;
	Point3d intersection(pt);
	intersection += r;

	color_rgb col = objects[0].getColor();
	return col;
}

void BasicEngine::render()
{
	unsigned int image_height = img.getHeight();
	unsigned int image_width = img.getWidth();
	std::vector<unsigned char> img_pixel = img.getData();

	for (unsigned int i = 0; i < image_height * image_width; i++)
	{
		// TODO
		//Properly set the things with the camera
		Vector3d ray_pixel(i / image_height, i % image_width, 0);
		Point3d pixel_position(i / image_height, i % image_width, 0);

		img.setPixel(trace(pixel_position, ray_pixel), i);
	}

	img.save("test_save.ppm");
}
