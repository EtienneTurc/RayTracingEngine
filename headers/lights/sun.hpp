#ifndef SUN_HPP
#define SUN_HPP

#include "lights/light.hpp"
#include "utils/color.hpp"
#include "utils/vector.hpp"

class Sun : public Light
{
  public:
	Sun(const Vector &vec, const color_rgb &c);

	Vector getDirectionToLight(const Vector &) const;

	bool isIntersectionAfterLight(const Vector &, const Vector &) const;
};

#endif //SUN_HPP
