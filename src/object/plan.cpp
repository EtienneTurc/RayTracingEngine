#include "object/plan.hpp"

Plan::Plan(const Vector3d norm, const float origin) : _origin(origin)
{
	_normal = norm;
	_normal.normalize();
}

float Plan::distance(const Point3d pt)
{
	return abs(_normal.x * pt.x + _normal.y * pt.y + _normal.z * pt.z + _origin);
}

Vector3d Plan::normal_at()
{
	return _normal;
};
