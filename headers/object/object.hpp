#ifndef _Object_HPP_
#define _Object_HPP_

#include "utils/point3d.hpp"
#include "utils/vector3d.hpp"
#include "type.hpp"

class Object
{
  public:
	Object(float op, color_rgb col) : _opacity(op), _color(col) {}
	~Object() {}

  protected:
	float distance(const Point3d pt);
	Vector3d normal_at();

  private:
	float _opacity;
	color_rgb _color;

	//   texture
};

#endif
