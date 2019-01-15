#ifndef _POINT3D_HPP_
#define _POINT3D_HPP_

template <class value_type> // int, float, float 128 ...
class Point3d
{
  public:
	value_type x, y, z;

	Point3d() : x(0), y(0), z(0) {}
	Point3d(value_type v) : x(v), y(v), z(v) {}
	Point3d(value_type xx, value_type yy, value_type zz) : x(xx), y(yy), z(zz) {}
	Point3d(const Point3d &pt) : x(pt.x), y(pt.y), z(pt.z) {}
	~Point3d() {}

	Point3d operator+(const Point3d &pt) const
	{
		return {x + pt.x, y + pt.y, z + pt.z};
	}

	Point3d operator-(const Point3d &u) const
	{
		return {this->x - u.x, this->y - u.y, this->z - u.z};
	}

	Point3d &operator+=(const Point3d &u)
	{
		this->x += u.x;
		this->y += u.y;
		this->z += u.z;
		return *this;
	}

	Point3d &operator-=(const Point3d &u)
	{
		this->x -= u.x;
		this->y -= u.y;
		this->z -= u.z;
		return *this;
	}
};

template <class charT, class traits = std::char_traits<charT>>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits> &stream, const Point3d &pt)
{
	stream << "{ " << pt.x << ", " << pt.y << ", " << pt.z << "}";
	return stream;
}

#endif