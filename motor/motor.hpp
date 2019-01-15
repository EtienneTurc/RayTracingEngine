#ifndef _MOTOR_HPP
#define _MOTOR_HPP
#include "scene.hpp"
#include "image.hpp"

class Motor
{
  public:
	Motor(Scene scene, Image img) : scene(scene), img(img) {}
	~Motor() {}

	virtual void render();
	virtual void trace();

  private:
	Scene scene;
	Image img;
};

#endif
