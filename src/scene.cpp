#include "scene.hpp"

Scene::Scene(Camera c, Screen s, std::vector<Light> l, std::vector<Triangle> t) : _camera(c), _screen(s), _lights(l), _objects(t) {}

void Scene::getObjectsIntersection(const Vector direction, int &index, Vector &intersection)
{
	index = -1;
	Vector tmp_intersection(0, 0, 0);
	int min_distance;
	Vector camera_position = _camera.getPosition();

	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i].isIntersecting(camera_position, direction, tmp_intersection))
		{
			float distance = (tmp_intersection - camera_position).getNorm();
			if (index == -1 || min_distance > distance)
			{
				intersection = tmp_intersection;
				min_distance = distance;
				index = i;
			}
		}
	}
}

void Scene::getContributingLights(const Vector intersection, const int index, std::vector<unsigned> &lights_seen)
{
	Vector intersection_pt(0, 0, 0);
	Vector direction_to_light;
	bool hidden;
	Vector camera_position = _camera.getPosition();

	for (unsigned l = 0; l < _lights.size(); l++)
	{
		hidden = false;
		direction_to_light = _lights[l].getPosition() - intersection - camera_position;

		for (int i = 0; i < _objects.size() && i != index; i++)
		{
			if (_objects[i].isIntersecting(intersection, direction_to_light, intersection_pt))
			{
				if ((intersection - intersection_pt).getNorm() < (intersection - _lights[l].getPosition() + camera_position).getNorm())
				{
					hidden = true;
					break;
				}
			}
		}

		if (!hidden)
			lights_seen.push_back(l);
	}
}

color_rgb Scene::computePixelColor(const std::vector<unsigned> lights_seen, const Vector obj_normal, const Vector intersection)
{
	color_rgb source = {0, 0, 0};
	for (unsigned l = 0; l < lights_seen.size(); l++)
	{
		unsigned light_index = lights_seen[l];
		Vector direction_to_light = _lights[light_index].getPosition() - intersection - _camera.getPosition();
		float intensity = obj_normal.dotProduct(direction_to_light.normalize());
		source = addSynthese(source, intensity * _lights[light_index].getColor());
	}
	return source;
}

void Scene::render()
{
	unsigned width = _screen.getWidth();
	unsigned height = _screen.getHeight();

	Vector camera_dir = _camera.getDirection();
	Vector screen_center = camera_dir.normalize() * _camera.getDistance();
	Vector camera_position = _camera.getPosition();

#pragma omp parallel for schedule(dynamic, 20)
	for (unsigned col = 0; col < width; col++)
	{
		for (unsigned row = 0; row < height; row++)
		{
			Vector direction = _screen.pixelDirection(row, col, screen_center);

			// initialisation
			int index;
			Vector intersection(0, 0, 0);

			// find if there is an intersectio
			getObjectsIntersection(direction, index, intersection);

			//Check light that contributes to the intersection point
			if (index > -1) // if intersect
			{
				std::vector<unsigned> lights_seen;

				getContributingLights(intersection, index, lights_seen);

				//set up the normal correctly
				Vector obj_normal = _objects[index].getNormalFromDirection(direction);

				// set the pixel color
				color_rgb source = computePixelColor(lights_seen, obj_normal, intersection);
				_screen.setPixelColor(row, col, subbSynthese(_objects[index].getColor(), source));
			}
		}
	}
	_screen.save("first_image.ppm");
}
