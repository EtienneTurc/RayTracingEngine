#include "scene.hpp"

Scene::Scene(Camera c, Screen s, std::vector<Light> l, std::vector<Triangle> t) : _camera(c), _screen(s), _lights(l), _objects(t) {}

void Scene::getObjectsIntersection(const Vector direction, const Vector point, int &index, Vector &intersection)
{
	index = -1;
	Vector tmp_intersection(0, 0, 0);
	int min_distance;

	for (int i = 0; i < _objects.size(); i++)
	{
		if (_objects[i].isIntersecting(point, direction, tmp_intersection))
		{
			float distance = (tmp_intersection - point).getNorm();
			if (index == -1 || min_distance > distance)
			{
				intersection = tmp_intersection;
				min_distance = distance;
				index = i;
			}
		}
	}
}

void Scene::getContributingLights(const Vector direction, const Vector intersection, const int index, std::vector<unsigned> &lights_seen, color_rgb &source, const int traced)
{
	Vector intersection_pt(0, 0, 0);
	Vector direction_to_light;
	bool hidden;
	Vector camera_position = _camera.getPosition();

	for (unsigned l = 0; l < _lights.size(); l++)
	{
		hidden = false;
		direction_to_light = _lights[l].getPosition() - intersection - camera_position;

		for (int i = 0; i < _objects.size(); i++)
		{
			if (index == i)
				continue;
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
	if (traced < 100 && lights_seen.size() == 0)
	{
		if (traced > 2)
		{
			std::cout << traced << "\n";
		}
		Vector v = _objects[index].getNormalFromDirection(direction);
		Vector u = -1 * direction;
		Vector p = u.dotProduct(v) * v;
		Vector new_direction = 2 * p - u;
		trace(-1 * intersection, new_direction, traced + 1, source);
	}
}

color_rgb Scene::computePixelColor(const std::vector<unsigned> lights_seen, const Vector obj_normal, const Vector intersection, const color_rgb source)
{
	color_rgb local_source = source;
	for (unsigned l = 0; l < lights_seen.size(); l++)
	{
		unsigned light_index = lights_seen[l];
		Vector direction_to_light = _lights[light_index].getPosition() - intersection - _camera.getPosition();
		float intensity = obj_normal.dotProduct(direction_to_light.normalize());
		local_source = addSynthese(local_source, intensity * _lights[light_index].getColor());
	}
	return local_source;
}

void Scene::trace(Vector point, Vector direction, int traced, color_rgb &source)
{
	int index;
	Vector intersection(0, 0, 0);

	// find if there is an intersection
	getObjectsIntersection(direction, point, index, intersection);

	//Check light that contributes to the intersection point
	if (index > -1) // if intersect
	{
		std::vector<unsigned> lights_seen;

		getContributingLights(direction, intersection, index, lights_seen, source, traced);

		//set up the normal correctly
		Vector obj_normal = _objects[index].getNormalFromDirection(direction);

		// set the pixel color
		color_rgb local_source = {0, 0, 0};
		local_source = computePixelColor(lights_seen, obj_normal, intersection, source);
		source = subbSynthese(_objects[index].getColor(), local_source);
	}
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
			// initialisation
			color_rgb source = {0, 0, 0};
			Vector direction = _screen.pixelDirection(row, col, screen_center);
			Vector camera_position = _camera.getPosition();

			trace(camera_position, direction, 1, source);

			_screen.setPixelColor(row, col, source);
		}
	}
	_screen.save("first_image.ppm");
}

void Scene::loaderObj(const std::string filename, const color_rgb col, const Vector translation, const Vector rotation)
{
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		std::vector<Vector> summits;
		while (getline(file, line))
		{
			std::string type = line.substr(0, 2);
			if (type == "v ")
			{
				std::istringstream v(line.substr(2));
				float x, y, z;
				v >> x;
				v >> y;
				v >> z;
				summits.push_back(Vector(x, y, z).rotate3D(rotation) + translation);
			}
			else if (type == "f ")
			{
				unsigned int summitIndex[3], normalIndex[3];
				const char *chh = line.c_str();
				sscanf(chh, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d\n", &summitIndex[0], &summitIndex[1], &summitIndex[2]);

				// Create a new triangle
				Triangle t(summits[summitIndex[0] - 1], summits[summitIndex[1] - 1], summits[summitIndex[2] - 1], col);
				_objects.push_back(t);
			}
			// std::cout << line << '\n';
		}
	}
	else
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(-1);
	}
}
