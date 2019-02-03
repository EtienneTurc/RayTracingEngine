#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

// #include "utils/point3d.hpp"

// class Point3d;

class Vector3d
{
  public:
	float x, y, z;

	Vector3d() : x(0), y(0), z(0) {}
	Vector3d(float v) : x(v), y(v), z(v) {}
	Vector3d(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	Vector3d(const Vector3d &dir) : x(dir.x), y(dir.y), z(dir.z) {}
	// Vector3d(&Point3d);
	~Vector3d() {}

	void normalize();
	void homothetie(const float a);

	Vector3d operator*(float scal)
	{
		this->x *= scal;
		this->y *= scal;
		this->z *= scal;
		return *this;
	}

	Vector3d operator=(Point3d &pt)
	{
		this->x = pt.x;
		this->y = pt.y;
		this->z = pt.z;
		return *this;
	}
};

template <class charT, class traits = std::char_traits<charT>>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits> &stream, const Vector3d &pt)
{
	stream << "{ " << pt.x << ", " << pt.y << ", " << pt.z << "}";
	return stream;
}

Vector3d prodVect(Vector3d, Vector3d);

#endif
