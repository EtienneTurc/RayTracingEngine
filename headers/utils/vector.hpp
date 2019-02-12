#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cmath>

class Vector
{
  private:
	float _x;
	float _y;
	float _z;

  public:
	Vector() {}
	Vector(float x, float y, float z);
	Vector(const Vector &v);
	~Vector() {}

	float x() const;
	float y() const;
	float z() const;

	Vector crossProduct(Vector v) const;
	float dotProduct(Vector v) const;
	Vector normalize() const;
	float getNorm() const;
};

Vector operator+(const Vector &v1, const Vector &v2);
Vector operator-(const Vector &v1, const Vector &v2);
Vector operator*(const Vector &v, const float lambda);
Vector operator*(const float lambda, const Vector &v);
bool operator==(const Vector &v1, const Vector &v2);
bool operator!=(const Vector &v1, const Vector &v2);

std::ostream &operator<<(std::ostream &stream, const Vector &v);

#endif //VECTOR_HPP