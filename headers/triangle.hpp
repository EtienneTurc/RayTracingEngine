#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/vector.hpp"
#include "utils/color.hpp"
#include "object.hpp"

class Triangle : public Object
{
  private:
	Vector _A;
	Vector _B;
	Vector _C;

	Vector getNormal() const;

  public:
	Triangle(const Vector A, const Vector B, const Vector C, const color_rgb col, const float transparency);
	~Triangle() {}

	bool isIntersecting(const Vector point, const Vector direction, Vector &intersection) const;
	Vector getNormalFromDirection(const Vector direction) const;
};

#endif //TRIANGLE_HPP
