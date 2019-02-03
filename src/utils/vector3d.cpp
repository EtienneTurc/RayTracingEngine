#include "utils/vector3d.hpp"
#include <math.h>

Vector3d::Vector3d(Point3d &pt) : x(pt.x), y(pt.y), z(pt.z) {}

void Vector3d::normalize()
{
	float sum = x * x + y * y + z * z;
	float norm = sqrt(sum);

	float inv_nrm = 1 / norm;
	x *= inv_nrm;
	y *= inv_nrm;
	z *= inv_nrm;
}

void Vector3d::homothetie(const float a)
{
	x *= a;
	y *= a;
	z *= a;
}

Vector3d prodVect(Vector3d u, Vector3d v) {
	Vector3d res(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
	res.normalize();
	return res;
}
