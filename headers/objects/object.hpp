#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "utils/vector.hpp"
#include "utils/color.hpp"

class Object
{
  private:
	color_rgb _color;
	float _transparency; //Between 0 and 1.

  public:
	Object(const color_rgb col, const float transparency);
	~Object() {}

	color_rgb getColor() const;
	float getTransparency() const;

	virtual bool isIntersecting(const Vector point, const Vector direction, Vector &intersection) const = 0;
	virtual Vector getNormalFromDirection(const Vector direction) const = 0;
};

#endif //OBJECT_HPP