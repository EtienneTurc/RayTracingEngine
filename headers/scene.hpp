#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <fstream>
// #include <stdlib.h>
#include <sstream>

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

	void getObjectsIntersection(const Vector direction, const Vector point, int &index, Vector &intersection);
	void getContributingLights(const Vector direction, const Vector intersection, const int index, std::vector<unsigned> &lights_seen, color_rgb &source, const int traced);
	color_rgb computePixelColor(const std::vector<unsigned> lights_seen, const Vector obj_normal, const Vector intersection, const color_rgb source);
	void trace(Vector intersection, Vector direction, int traced, color_rgb &source);

  public:
	Scene(Camera c, Screen s, std::vector<Light> l, std::vector<Triangle> t);
	~Scene() {}

	void render();
	void loaderObj(const std::string filename, const color_rgb col, const Vector translation, const Vector rotation);
};

#endif //SCENE_HPP
