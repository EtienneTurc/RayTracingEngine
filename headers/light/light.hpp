#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_
#include "utils/vector3d.hpp"
#include "utils/point3d.hpp"
#include <cstdint>
#include <array>

typedef std::array<uint8_t, 3> color_rgb;
class Light
{
  public:
	Light()
	{
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
	}
	Light(uint8_t r, uint8_t g, uint8_t b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
	Light(color_rgb col) : color(col) {}
	~Light() {}

	color_rgb getCol() { return color; }

  private:
	color_rgb color;
};

#endif
