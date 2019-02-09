#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/vector.hpp"
#include "utils/types.hpp"

class Triangle
{
  private:
	Vector _A;
	Vector _B;
	Vector _C;
	color_rgb _color;

  public:
	Triangle(const Vector A, const Vector B, const Vector C, const color_rgb col);
	~Triangle() {}

	Vector getNormal() const;
	color_rgb getColor() const;

	bool isIntersecting(const Vector point, const Vector direction, Vector &intersection);
};

#endif //TRIANGLE_HPP
