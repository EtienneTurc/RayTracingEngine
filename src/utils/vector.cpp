#include "utils/vector.hpp"

Vector::Vector(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vector::Vector(const Vector &v) : _x(v.x()), _y(v.y()), _z(v.z()) {}

float Vector::x() const
{
	return _x;
}

float Vector::y() const
{
	return _y;
}

float Vector::z() const
{
	return _z;
}

Vector Vector::crossProduct(Vector v) const
{
	return Vector(_y * v.z() - _z * v.y(), _z * v.x() - _x * v.z(), _x * v.y() - _y * v.x());
}

float Vector::dotProduct(Vector v) const
{
	return _x * v.x() + _y * v.y() + _z * v.z();
}

Vector Vector::normalize() const
{
	float norm = getNorm();
	float x = _x / norm;
	float y = _y / norm;
	float z = _z / norm;
	return Vector(x, y, z);
}

float Vector::getNorm() const
{
	return sqrt(_x * _x + _y * _y + _z * _z);
}

Vector Vector::rotate3D(Vector rot)
{
	float angleX = rot.x();
	float angleY = rot.y();
	float angleZ = rot.z();

	float sinX = sin(angleX), cosX = cos(angleX);
	float sinY = sin(angleY), cosY = cos(angleY);
	float sinZ = sin(angleZ), cosZ = cos(angleZ);

	float x = _x * cosY - _z * sinY + _x * cosZ - _y * sinZ;
	float y = _y * cosX - _z * sinX + _y * cosZ + _x * sinZ;
	float z = _z * cosX + _y * sinX + _z * cosY + _x * sinY;
	return Vector(0.5 * x, 0.5 * y, 0.5 * z);
}

Vector operator+(const Vector &v1, const Vector &v2)
{
	return Vector(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

Vector operator-(const Vector &v1, const Vector &v2)
{
	return Vector(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

Vector operator*(const Vector &v, const float lambda)
{
	return Vector(v.x() * lambda, v.y() * lambda, v.z() * lambda);
}

Vector operator*(const float lambda, const Vector &v)
{
	return v * lambda;
}

bool operator==(const Vector &v1, const Vector &v2)
{

	return (v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z());
}

bool operator!=(const Vector &v1, const Vector &v2)
{

	return (v1.x() != v2.x() || v1.y() != v2.y() || v1.z() != v2.z());
}

std::ostream &operator<<(std::ostream &stream, const Vector &v)
{
	stream << "( " << v.x() << ", " << v.y()
		   << ", " << v.z()
		   << ")";
	return stream;
}
