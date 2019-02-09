#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/vector.hpp"

class Triangle
{
  private:
	Vector _A;
	Vector _B;
	Vector _C;

  public:
	Triangle(const Vector A, const Vector B, const Vector C);
	~Triangle() {}

	Vector getNormal() const;

	bool isIntersecting(const Vector point, const Vector direction, Vector &intersection);
};

#endif //TRIANGLE_HPP
