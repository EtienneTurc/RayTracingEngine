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
	Light _light;

  public:
	Scene(Camera c, Screen s, Light l, std::vector<Triangle> t);
	~Scene() {}

	void render();
};

#endif //SCENE_HPP
