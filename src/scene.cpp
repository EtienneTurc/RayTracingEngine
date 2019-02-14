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

		float transparency = _objects[index].getTransparency();

		// reflexion
		color_rgb reflexion_source = {0, 0, 0};
		if (traced < 100 && lights_seen.size() == 0)
		{
			Vector v = _objects[index].getNormalFromDirection(direction);
			Vector u = -1 * direction;
			Vector p = u.dotProduct(v) * v;
			Vector new_direction = 2 * p - u;
			trace(intersection, new_direction, traced + 1, reflexion_source);
		}

		//Transparency
		color_rgb transparency_source = {0, 0, 0};
		if (traced < 10 && lights_seen.size() == 0)
		{
			trace(intersection, direction, traced + 1, transparency_source);
		}

		// std::cout << "New\n";
		// std::cout << source << "\n";
		// std::cout << transparency << "\n";
		// std::cout << reflexion_source << "\n";
		// std::cout << reflex << "\n";
		// std::cout << transparency_source << "\n";
		// std::cout << transp << "\n";
		// transparency_source = transp * transparency * transparency_source;
		// std::cout << transparency_source << "\n";
		// std::cout << source << "\n";

		//set up the normal correctly
		Vector obj_normal = _objects[index].getNormalFromDirection(direction);

		// set the pixel color
		color_rgb local_source = {0, 0, 0};
		local_source = computePixelColor(lights_seen, obj_normal, intersection, reflexion_source);
		// std::cout << local_source << "\n";
		local_source = addSynthese((1 - transparency) * local_source, transparency * transparency_source);
		// std::cout << local_source << "\n";
		source = subbSynthese(_objects[index].getColor(), local_source);
		// std::cout << source << "\n";
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
				// std::cout << summits.back() << "\n";
				// std::cout << line.substr(2) << "\n";
			}
			else if (type == "f ")
			{
				// std::cout << "f\n";
				std::vector<unsigned> index_summits;
				std::string sub_line = line.substr(1);
				while (sub_line.length() > 1)
				{
					unsigned index_value;
					const char *chh = sub_line.c_str();
					// std::cout << "before scanf\n";
					sscanf(chh, " %d/", &index_value);
					// std::cout << index_value << " index\n";
					index_summits.push_back(index_value);
					int i = 1;
					if (sub_line[i] == ' ')
					{
						++i;
					}

					while (sub_line[i] != ' ' && i < sub_line.length() - 1)
					{
						++i;
					}

					sub_line = sub_line.substr(i);
					// std::cout << i << " i, sub: " << sub_line.substr(i) << "\n";
					// std::cout << sub_line << "\n";
				}

				// for (unsigned i = 0; i < index_summits.size(); ++i)
				// {
				// 	std::cout << summits[index_summits[i]] << ", ";
				// }
				// std::cout << "\n";

				//create traingle
				for (unsigned i = 1; i < index_summits.size() - 1; ++i)
				{
					Triangle t(summits[index_summits[0] - 1], summits[index_summits[i] - 1], summits[index_summits[i + 1] - 1], col);
					_objects.push_back(t);
				}
			}
			// }
			// std::cout << line << '\n';
		}
	}
	else
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(-1);
	}
}
