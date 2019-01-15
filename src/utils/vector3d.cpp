#include "utils/vector3d.hpp"
#include <math.h>

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
