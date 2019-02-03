#ifndef BASIC_ENGINE_HPP
#define BASIC_ENGINE_HPP
#include "engine.hpp"

class BasicEngine : public Engine
{
  public:
	BasicEngine(Scene scene, Image img) : Engine(scene, img) {}
	~BasicEngine() {}

	void render();
	color_rgb trace(const Point3d pt, const Vector3d ray);
	float minDistanceToObject(const Point3d pt, const Vector3d ray);
};

#endif
