#include "objects/triangle.hpp"
#include "utils/params.hpp"

Triangle::Triangle(const Vector &A, const Vector &B, const Vector &C, const color_rgb &col, float transparency, float reflexivity) : Object(col, transparency, reflexivity), _A(A), _B(B), _C(C) {}

Vector Triangle::getNormal() const
{
	Vector edge1 = _A - _B;
	Vector edge2 = _A - _C;
	return edge1.crossProduct(edge2);
}

Vector Triangle::getNormalFromDirection(const Vector &direction) const
{
	Vector obj_normal = this->getNormal().normalize();
	bool is_good_normal = obj_normal.dotProduct(direction) < 0;
	if (!is_good_normal)
	{
		obj_normal = -1 * obj_normal;
	}
	return obj_normal;
}

bool Triangle::isIntersecting(const Vector &point, const Vector &direction, Vector &intersection) const
{
	Vector edge1 = (_B - _A);
	Vector edge2 = (_C - _A);

	Vector orthogonal = direction.crossProduct(edge2);
	float is_parallel = edge1.dotProduct(orthogonal);

	if (is_parallel > -EPSILON && is_parallel < EPSILON)
		return false; // This ray is parallel to this triangle.

	float deviation = 1.0 / is_parallel;
	Vector distance = (point - _A);
	float u = deviation * (distance.dotProduct(orthogonal));

	if (u < 0.0 || u > 1.0)
		return false;

	Vector q = distance.crossProduct(edge1);
	float v = deviation * direction.dotProduct(q);
	if (v < 0.0 || u + v > 1.0)
		return false;

	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = deviation * edge2.dotProduct(q);
	if (t > EPSILON) // ray intersection
	{
		intersection = point + direction * t;
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}
