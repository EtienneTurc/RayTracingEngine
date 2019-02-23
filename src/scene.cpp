#include "scene.hpp"
#include "utils/params.hpp"

Scene::Scene(Camera c, Screen s, std::vector<Light *> l, std::vector<Object *> t, unsigned recursion_level) : _camera(c), _screen(s), _lights(l), _objects(t), _recursion_level(recursion_level) {}

Scene::~Scene()
{
	for (size_t i = 0; i < _objects.size(); i++)
	{
		delete _objects[i];
	}
}

int Scene::getObjectsIntersection(const Vector &direction, const Vector &point, int actual_obj, Vector &intersection) const
{
	int index = -1;
	Vector tmp_intersection(0, 0, 0);
	double min_distance = -1;

	for (size_t i = 0; i < _objects.size(); i++)
	{
		// if (actual_obj != (int)i && _objects[i]->isIntersecting(point, direction, tmp_intersection))
		if (_objects[i]->isIntersecting(point, direction, tmp_intersection))
		{
			double distance = (tmp_intersection - point).getNorm();
			if ((index == -1 || min_distance > distance) && distance > EPSILON)
			{
				intersection = tmp_intersection;
				min_distance = distance;
				index = i;
			}
		}
	}
	return index;
}

color_rgb Scene::getLightContribution(const Vector &point, const Vector &direction, int light_index, int actual_obj, int deep) const
{
	if (deep == 0)
		return {0, 0, 0};

	Vector intersection(0, 0, 0);

	int index = getObjectsIntersection(direction, point, actual_obj, intersection);

	// If intersection is not found or is after the light
	if (index == -1 || _lights[light_index]->isIntersectionAfterLight(point, intersection))
		return _lights[light_index]->getColor();

	return _objects[index]->getTransparency() * getLightContribution(intersection, direction, light_index, index, deep - 1) + (0.2 * _objects[actual_obj]->getColor());
}

color_rgb Scene::getLightsContribution(const Vector &point, const Vector &obj_normal, int actual_obj) const
{
	Vector direction_to_light;
	color_rgb source = {0, 0, 0};
	color_rgb loc_source = {0, 0, 0};
	Vector intersection_pt = {0, 0, 0};
	int deep = _recursion_level;

	for (unsigned l = 0; l < _lights.size(); l++)
	{
		direction_to_light = _lights[l]->getDirectionToLight(point);

		loc_source = getLightContribution(point, direction_to_light, l, actual_obj, deep);

		float intensity = obj_normal.dotProduct(direction_to_light.normalize());
		if (intensity < 0)
			intensity = 0;
		source = addSynthese(intensity * loc_source, source);
	}

	return source;
}

color_rgb Scene::trace(const Vector &point, const Vector &direction, int actual_obj, int traced) const
{

	Vector intersection(0, 0, 0);

	// find if there is an intersection
	int index = getObjectsIntersection(direction, point, actual_obj, intersection);

	//Check light that contributes to the intersection point
	if (index > -1) // if intersect
	{
		color_rgb local_source = {0, 0, 0};
		color_rgb transparency_source = {0, 0, 0};
		color_rgb reflexion_source = {0, 0, 0};
		float transparency = _objects[index]->getTransparency();
		float reflexivity = _objects[index]->getReflexivity();
		Vector obj_normal = _objects[index]->getNormal(intersection, direction);

		// //Transparency
		// if (traced > 0)
		// {
		// 	transparency_source = trace(intersection, direction, index, traced - 1);
		// }

		// Reflexion
		if (traced > 0)
		{
			Vector u = -1 * direction;
			Vector p = u.dotProduct(obj_normal) * obj_normal;
			Vector new_direction = 2 * p - u;

			reflexion_source = trace(intersection, new_direction, index, traced - 1);
		}

		// Light color
		color_rgb lights_color = {0, 0, 0};
		lights_color = getLightsContribution(intersection, obj_normal, index);

		// set the pixel color
		local_source = (1 - reflexivity) * lights_color * _objects[index]->getColor() + reflexivity * reflexion_source;
		return (1 - transparency) * local_source + transparency * transparency_source;
	}
	// if (traced == _recursion_level)
	// 	return {0, 0, 0};
	return {205, 197, 188};
}

void Scene::render()
{
	unsigned width = _screen.getWidth();
	unsigned height = _screen.getHeight();
	unsigned steps = 0;

	Vector camera_dir = _camera.getDirection();
	Vector screen_center = camera_dir.normalize() * _camera.getDistance();
	Vector camera_position = _camera.getPosition();
	std::vector<Offset> pixels_offset = _screen.getPixelsOffset();

#pragma omp parallel for schedule(dynamic, 20)
	for (unsigned col = 0; col < width; col++)
	{
		for (unsigned row = 0; row < height; row++)
		{
			// initialisation
			color_rgb source = {0, 0, 0};
			// Antialiasing
			for (Offset offset : pixels_offset)
			{
				Vector direction = _screen.pixelDirection(row, col, offset.right, offset.bottom, screen_center);
				color_rgb local_source = trace(camera_position, direction, -1, _recursion_level);
				source = addSynthese(offset.weight * local_source, source);
			}

			_screen.setPixelColor(row, col, source);
		}

		//Progress status
		if (col % 200 == 0)
		{
			steps < col ? steps = col : steps = steps;
			std::cout << "Progress " << (float)steps / (float)width * 100 << " %";
			std::cout << "\n";
		}
	}
	_screen.save("first_image.ppm");
}
