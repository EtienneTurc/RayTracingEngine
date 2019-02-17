#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/vector.hpp"
#include "utils/color.hpp"

class Triangle
{
  private:
	Vector _A;
	Vector _B;
	Vector _C;
	color_rgb _color;
	float _transparency; //Between 0 and 1.
	float _reflexivity;  //Between 0 and 1.

  public:
	Triangle(const Vector &A, const Vector &B, const Vector &C, const color_rgb &col, float transparency, float reflexivity);
	~Triangle() {}

	Vector getNormal() const;
	color_rgb getColor() const;
	float getTransparency() const;
	float getReflexivity() const;

	Vector getNormalFromDirection(const Vector &direction) const;
	bool isIntersecting(const Vector &point, const Vector &direction, Vector &intersection) const;
};

#endif //TRIANGLE_HPP
