#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "utils/vector.hpp"
#include "utils/color.hpp"
#include "object.hpp"

class Sphere : public Object
{
  private:
	Vector _center;
	float _radius;

  public:
	Sphere(const Vector center, const float radius, const color_rgb col, const float transparency);
	~Sphere();

	bool isIntersecting(const Vector point, const Vector direction, Vector &intersection) const;
	Vector getNormalFromDirection(const Vector direction);
};

#endif //SPHERE_HPP
