#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "utils/vector.hpp"
#include "utils/color.hpp"
#include "utils/texture.hpp"
#include "utils/type.hpp"
#include "object.hpp"

class Triangle : public Object
{
  private:
	Vector _A;
	Vector _B;
	Vector _C;
	bool _enabled_uv = false;
	vec2 _A_uv;
	vec2 _B_uv;
	vec2 _C_uv;
	texture *_texture;

	Vector getObjectNormal() const;

  public:
	Triangle(const Vector &A, const Vector &B, const Vector &C, const color_rgba &col, float transparency, float reflexivity);
	Triangle(const Vector &A, const Vector &B, const Vector &C, const vec2 &A_uv, const vec2 &B_uv, const vec2 &C_uv, texture *t, float transparency, float reflexivity);
	~Triangle() {}

	color_rgba getColor(const Vector &point);
	Vector getNormal(const Vector &, const Vector &direction) const;

	bool isIntersecting(const Vector &point, const Vector &direction, Vector &intersection) const;
};

#endif //TRIANGLE_HPP
