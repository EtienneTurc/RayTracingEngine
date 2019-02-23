#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
// #include <stdlib.h>

#include "camera.hpp"
#include "screen.hpp"
#include "lights/light.hpp"
#include "objects/object.hpp"

class Scene
{
  private:
	Camera _camera;
	Screen _screen;
	std::vector<Light *> _lights;
	std::vector<Object *> _objects;
	unsigned _recursion_level;

	int getObjectsIntersection(const Vector &direction, const Vector &point, int actual_obj, Vector &intersection) const;

	color_rgba getLightContribution(const Vector &start_point, const Vector &direction, int light_index, int actual_obj, int deep) const;
	color_rgba getLightsContribution(const Vector &point, const Vector &obj_normal, int actual_obj) const;

	color_rgba trace(const Vector &intersection, const Vector &direction, int actual_obj, int traced) const;

  public:
	Scene(Camera c, Screen s, std::vector<Light *> l, std::vector<Object *> t, unsigned recursion_level);
	~Scene();

	void render();
};

#endif //SCENE_HPP
