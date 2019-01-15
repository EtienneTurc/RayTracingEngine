#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_
#include "point3d.hpp"

template <class value_type> // int, float, float 128 ...
class Vector3d
{
  public:
	value_type x, y, z;

	Vector3d() : pt(0), {}
	Vector3d(value_type xx, value_type yy, value_type zz) : x(xx), y(yy), z(zz) {}
	Vector3d(value_type v) : x(v), y(v), z(v) {}
	Point3d(const Vector3d &dir) : x(dir.x), y(dir.y), z(dir.z) {}
	~Vector3d() {}

	void normalize();
	void homothetie(const value_type a);
};

template <class charT, class traits = std::char_traits<charT>>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits> &stream, const Vector3d &pt)
{
	stream << "{ " << pt.x << ", " << pt.y << ", " << pt.z << "}";
	return stream;
}

#endif
