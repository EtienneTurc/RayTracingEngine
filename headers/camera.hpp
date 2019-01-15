#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_
#include "utils/point3d.hpp"
#include "utils/vector3d.hpp"

class Camera
{
  public:
	Camera() : position(0), direction(1, 0, 0) {}
	Camera(const Point3d &pos, const Vector3d &dir) : position(pos), direction(dir) {}
	~Camera() = default;

	void move(const Point3d &pos);

  private:
	Point3d position;
	Vector3d direction;
};

#endif
