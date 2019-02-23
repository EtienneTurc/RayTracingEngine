#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "utils/vector.hpp"
#include "utils/color.hpp"

class Object
{
  protected:
	color_rgba _color;
	float _transparency; //Between 0 and 1.
	float _reflexivity;  //Between 0 and 1.

  public:
	Object() {}
	Object(const color_rgba &col, float transparency, float reflexivity);
	virtual ~Object() {}

	virtual color_rgba getColor(const Vector &point);
	float getTransparency() const;
	float getReflexivity() const;

	virtual bool isIntersecting(const Vector &point, const Vector &direction, Vector &intersection) const = 0;
	virtual Vector getNormal(const Vector &point, const Vector &direction) const = 0;
};

#endif //OBJECT_HPP
