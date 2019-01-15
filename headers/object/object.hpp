#ifndef _Object_HPP_
#define _Object_HPP_

#include "utils/point3d.hpp"
#include "utils/vector3d.hpp"

class Object
{
  public:
	Object() {}
	~Object() {}

	//   protected:
	virtual float distance(const Point3d pt) = 0;
	virtual Vector3d normal_at() = 0;

  private:
};

#endif
