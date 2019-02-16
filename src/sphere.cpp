#include "sphere.hpp"

Sphere::Sphere(const Vector center, const float radius, const color_rgb col, const float transparency) : _center(center), _radius(radius), Object(col, transparency) {}

bool Sphere::isIntersecting(const Vector point, const Vector direction, Vector &intersection) const
{
	float dist = (_center - point).crossProduct(direction).getNorm() / direction.getNorm();

	if (dist > _radius)
	{
		return false;
	}

	//compute intersection (closest to point)
	//Equation At² + Bt + C = 0
	float A = direction.getNorm() * direction.getNorm();
	float B = 2 * (point.x() - _center.x() + point.y() - _center.y() + point.z() - _center.z());
	float C = (point - _center).getNorm() - _radius * _radius;

		return true;
}