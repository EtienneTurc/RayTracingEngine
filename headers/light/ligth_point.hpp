#ifndef _LIGHT_POINT_HPP_
#define _LIGHT_POINT_HPP_
#include "light.hpp"
#include "point3d.hpp"

template <class value_type>
class Light_point : public Light
{
  public:
	Light_point() : Light(), pt(0) {}
	Light_point(const point3d pos) : Light(), pt(pos) {}
	Light_point(const point3d pos, const color_rgb col) : Light(col), pt(pos) {}
	Light_point(const point3d pos, uint8_t r, uint8_t g, uint8_t b) : Light(r, g, b), pt(pos) {}
	~Light_point() {}

	Point3d getPoint() { return pt; }

  private:
	Point3d pt;
};

#endif
