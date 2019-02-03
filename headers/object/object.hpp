#ifndef _Object_HPP_
#define _Object_HPP_

#include <vector>
#include <array>
#include <iostream>
#include <sstream>

#include "utils/point3d.hpp"
#include "utils/vector3d.hpp"
#include "type.hpp"

class Object
{
  public:
	Object(float op, color_rgb col) : _opacity(op), _color(col) {}
	~Object() {}

	//   protected:
	float distance(const Point3d pt) {}
	float distance(const Point3d pt, const Vector3d vec) {}
	Vector3d normal_at();

	color_rgb getColor();

  private:
	float _opacity;
	color_rgb _color;

	//   texture
};

#endif
