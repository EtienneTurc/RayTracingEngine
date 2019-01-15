#ifndef _PLAN_HPP_
#define _PLAN_HPP_

#include "object/object.hpp"

class Plan : public Object
{
  public:
	Plan(const Vector3d norm, const float origin);
	~Plan() {}

	float distance(const Point3d pt);
	Vector3d normal_at();

  private:
	/*
	plan described by ax + by + cz + d = 0
	with the normal (a, b, c) and d the origin
    */
	Vector3d _normal;
	float _origin; // d
};

#endif
