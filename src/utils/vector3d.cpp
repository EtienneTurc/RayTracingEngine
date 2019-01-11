#include "vector3d.hpp"
#include <math.h>

template <class value_type>
void Vector3d<value_type>::normalize()
{
	value_type sum = x * x + y * y + z * z;
	value_type norm = sqrt(sum);

	value_type inv_nrm = 1 / norm;
	x *= inv_nrm;
	y *= inv_nrm;
	z *= inv_nrm;
	return *this;
}

template <class value_type>
void Vector3d<value_type>::homothetie(const value_type a)
{
	x *= a;
	y *= a;
	z *= a;
}
