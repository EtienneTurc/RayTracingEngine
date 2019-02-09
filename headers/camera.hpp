#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/vector.hpp"

class Camera
{
  private:
	Vector _position;
	Vector _direction;
	float _dist_normal;

  public:
	Camera(Vector pos, Vector dir, float dist_n);
	~Camera() {}

	Vector getDirection() const;
	Vector getPosition() const;
	float getDistance() const;
};

#endif //CAMERA_HPP
