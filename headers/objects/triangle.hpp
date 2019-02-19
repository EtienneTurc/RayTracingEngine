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

  public:
	Triangle(const Vector &A, const Vector &B, const Vector &C, const color_rgb &col, float transparency, float reflexivity);
	~Triangle() {}

	Vector getNormal() const;

	Vector getNormalFromDirection(const Vector &direction) const;
	bool isIntersecting(const Vector &point, const Vector &direction, Vector &intersection) const;
};

#endif //TRIANGLE_HPP
