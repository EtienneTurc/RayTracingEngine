#include "objects/sphere.hpp"
#include "utils/params.hpp"

Sphere::Sphere(const Vector &center, float radius, const color_rgb &col, float transparency, float reflexivity) : _center(center), _radius(radius), Object(col, transparency, reflexivity) {}

bool Sphere::isIntersecting(const Vector point, const Vector direction, Vector &intersection) const
{
	//compute intersection (closest to point)
	//Equation At² + Bt + C = 0
	float A = direction.getNorm() * direction.getNorm();
	float B = 2 * (point.x() - _center.x() + point.y() - _center.y() + point.z() - _center.z());
	float C = (point - _center).getNorm() - _radius * _radius;

	float delta = B * B - 4 * A * C;
	if (delta < -EPSILON)
	{
		return false;
	}
	else if (delta > EPSILON)
	{
		float t1 = (-B + sqrt(delta)) / (2 * A);
		float t2 = (-B - sqrt(delta)) / (2 * A);
		Vector p1 = point + t1 * direction;
		Vector p2 = point + t2 * direction;
		(point - p1).getNorm() < (point - p2).getNorm() ? intersection = p1 : intersection = p2;
		return true;
	}
	else
	{
		float t = -B / (2 * A);
		intersection = point + t * direction;
		return true;
	}

	return true;
}

Vector getNormalFromDirection(const Vector direction)
{
	return Vector(0, 0, 0);
}
