#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>

#include "camera.hpp"
#include "screen.hpp"
#include "light.hpp"
#include "triangle.hpp"

class Scene
{
  private:
	Camera _camera;
	Screen _screen;
	std::vector<Triangle> _objects;
	std::vector<Light> _lights;

	int getObjectsIntersection(const Vector &direction, const Vector &point, int actual_obj, Vector &intersection) const;

	color_rgb getLightContribution(const Vector &start_point, const Vector &direction, int light_index, int actual_obj, int deep) const;
	color_rgb getLightsContribution(const Vector &point, const Vector &obj_normal, int actual_obj) const;

	color_rgb trace(const Vector &intersection, const Vector &direction, int actual_obj, int traced) const;

  public:
	Scene(Camera c, Screen s, std::vector<Light> l, std::vector<Triangle> t);
	~Scene() {}

	void render();
};

#endif //SCENE_HPP
