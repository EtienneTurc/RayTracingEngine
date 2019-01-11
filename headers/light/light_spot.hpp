#ifndef _MANDELBULB_LIGHT_SPOT_HPP_
#define _MANDELBULB_LIGHT_SPOT_HPP_
#include "light.hpp"
#include "vector3d.hpp"
#include "point3d.hpp"

template <class value_type>
class Light_spot : public Light
{
  public:
	Light_spot() : Light(), direction(0), position(0), angle(0) {}
	Light_spot(const Vector3d dir, const Point3d pt, const value_type a) : Light(), direction(dir), position(pt), angle(a)) {}
	Light_spot(const Vector3d dir, const Point3d pt, const value_type a, const color_rgb col) : Light(col), direction(dir), position(pt), angle(a)) {}
	Light_spot(const Vector3d dir, const Point3d pt, const value_type a, uint8_t r, uint8_t g, uint8_t b) : Light(r, g, b), direction(dir), position(pt), angle(a)) {}
	~Light_spot() {}

  private:
	Point3d position;
	Vector3d direction;
	value_type angle;
};

#endif
