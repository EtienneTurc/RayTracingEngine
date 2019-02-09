#include "scene.hpp"

Scene::Scene(Camera c, Screen s, Light l, std::vector<Triangle> t) : _camera(c), _screen(s), _light(l), _objects(t) {}

void Scene::render()
{
	unsigned width = _screen.getWidth();
	unsigned height = _screen.getHeight();

	Vector camera_dir = _camera.getDirection();
	Vector screen_center = camera_dir.normalize() * _camera.getDistance();
	Vector camera_position = _camera.getPosition();

	for (unsigned row = 0; row < height; row++)
	{
		for (unsigned col = 0; col < width; col++)
		{
			Vector direction = _screen.pixelDirection(row, col, screen_center);

			int size = _objects.size();
			int min_distance;
			int index = -1;
			Vector intersection(0, 0, 0);
			for (int i = 0; i < size; i++)
			{
				if (_objects[i].isIntersecting(camera_position, direction, intersection))
				{
					std::cout << "hi\n";
					float distance = (intersection - camera_position).getNorm();
					if (index == -1 || min_distance > distance)
					{
						min_distance = distance;
						index = i;
					}
				}
			}
			if (index > -1)
			{
				std::cout << "set color\n";
				_screen.setPixelColor(row, col, _light.getColor());
			}
		}
	}
	_screen.save("first_image.ppm");
}
