#ifndef _ENGINE_HPP
#define _ENGINE_HPP
#include "scene.hpp"
#include "image.hpp"
#include "type.hpp"

class Engine
{
  public:
	Engine(Scene scene, Image img) : scene(scene), img(img) {}
	~Engine() {}

  protected:
	void render();
	color_rgb trace(const Point3d pt, const Vector3d ray);
	Scene scene;
	Image img;
};

#endif
