#ifndef _MOTOR_HPP
#define _MOTOR_HPP
#include "scene.hpp"
#include "image.hpp"
#include "type.hpp"

class Motor
{
  public:
	Motor(Scene scene, Image img) : scene(scene), img(img) {}
	~Motor() {}

  protected:
	void render();
	color_rgb trace();

  private:
	Scene scene;
	Image img;
};

#endif
