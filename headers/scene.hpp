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

	void getObjectsIntersection(const Vector direction, int &index, Vector &intersection);
	void getContributingLights(const Vector intersection, const int index, std::vector<unsigned> &lights_seen);
	color_rgb computePixelColor(const std::vector<unsigned> lights_seen, const Vector obj_normal, const Vector intersection);

  public:
	Scene(Camera c, Screen s, std::vector<Light> l, std::vector<Triangle> t);
	~Scene() {}

	void render();
};

#endif //SCENE_HPP
