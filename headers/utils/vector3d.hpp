#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_
#include "point3d.hpp"

class Vector3d
{
  public:
	float x, y, z;

	Vector3d() : x(0), y(0), z(0) {}
	Vector3d(float v) : x(v), y(v), z(v) {}
	Vector3d(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	Vector3d(const Vector3d &dir) : x(dir.x), y(dir.y), z(dir.z) {}
	Vector3d(const Point3d pt): x(pt.x), y(pt.y), z(pt.z){}
	~Vector3d() {}

	void normalize();
	void homothetie(const float a);

};

template <class charT, class traits = std::char_traits<charT>>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits> &stream, const Vector3d &pt)
{
	stream << "{ " << pt.x << ", " << pt.y << ", " << pt.z << "}";
	return stream;
}

Vector3d prodVect(Vector3d, Vector3d);

#endif
