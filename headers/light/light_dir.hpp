#ifndef _LIGHT_DIR_HPP_
#define _LIGHT_DIR_HPP_
#include "light.hpp"

class Light_dir : public Light
{
  public:
	Light_dir() : Light(), direction(0) {}
	Light_dir(const Vector3d dir) : Light(), direction(dir) {}
	Light_dir(const Vector3d dir, const color_rgb col) : Light(col), direction(dir) {}
	Light_dir(const Vector3d dir, uint8_t r, uint8_t g, uint8_t b) : Light(r, g, b), direction(dir) {}
	~Light_dir() {}

	Vector3d getDirection() { return direction; }

  private:
	Vector3d direction;
};
#endif
