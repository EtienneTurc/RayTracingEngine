#include "objects/triangle.hpp"
#include "utils/params.hpp"

Triangle::Triangle(const Vector &A, const Vector &B, const Vector &C, const color_rgba &col, float opacity, float reflexivity) : Object(col, opacity, reflexivity), _A(A), _B(B), _C(C) {}

Triangle::Triangle(const Vector &A, const Vector &B, const Vector &C, const vec2 &A_uv, const vec2 &B_uv, const vec2 &C_uv, texture *t, float opacity, float reflexivity)
{
	_A = A;
	_B = B;
	_C = C;
	_opacity = opacity;
	_reflexivity = reflexivity;
	_A_uv = A_uv;
	_B_uv = B_uv;
	_C_uv = C_uv;
	_enabled_uv = true;
	_texture = t;
}

Vector Triangle::getObjectNormal() const
{
	Vector edge1 = _A - _B;
	Vector edge2 = _A - _C;
	return edge1.crossProduct(edge2);
}

Vector Triangle::getNormal(const Vector &, const Vector &direction) const
{
	Vector obj_normal = this->getObjectNormal().normalize();
	bool is_good_normal = obj_normal.dotProduct(direction) < 0;
	if (!is_good_normal)
	{
		obj_normal = -1 * obj_normal;
	}
	return obj_normal;
}

color_rgba Triangle::getColor(const Vector &point)
{
	if (!_enabled_uv)
		return Object::getColor(point);

	// Barycentrique coordinate
	Vector u = _B - _C;
	Vector v = _A - _C;
	Vector a = (point - _C).crossProduct(u);
	Vector b = (point - _C).crossProduct(v);
	Vector tot = u.crossProduct(v);
	double tot_area = tot.getNorm();

	double alpha = a.getNorm() / tot_area;
	double beta = b.getNorm() / tot_area;
	double gamma = 1 - alpha - beta;

	// std::cout << "alpha " << alpha << "\n";
	// std::cout << "beta " << beta << "\n";
	// std::cout << "gamma " << gamma << "\n";

	vec2 text = {alpha * _A_uv[0] + beta * _B_uv[0] + gamma * _C_uv[0], alpha * _A_uv[1] + beta * _B_uv[1] + gamma * _C_uv[1]};

	// std::cout << "Intersection point " << point << "\n";
	// std::cout << "Texture " << text[0] << " " << text[1] << "\n";

	return _texture->sample(text[0], text[1]);
}

bool Triangle::isIntersecting(const Vector &point, const Vector &direction, Vector &intersection) const
{
	Vector edge1 = (_B - _A);
	Vector edge2 = (_C - _A);

	Vector orthogonal = direction.crossProduct(edge2);
	double is_parallel = edge1.dotProduct(orthogonal);

	if (is_parallel > -EPSILON && is_parallel < EPSILON)
		return false; // This ray is parallel to this triangle.

	double deviation = 1.0 / is_parallel;
	Vector distance = (point - _A);
	double u = deviation * (distance.dotProduct(orthogonal));

	if (u < 0.0 || u > 1.0)
		return false;

	Vector q = distance.crossProduct(edge1);
	double v = deviation * direction.dotProduct(q);
	if (v < 0.0 || u + v > 1.0)
		return false;

	// At this stage we can compute t to find out where the intersection point is on the line.
	double t = deviation * edge2.dotProduct(q);
	if (t > EPSILON) // ray intersection
	{
		intersection = point + direction * t;
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}
