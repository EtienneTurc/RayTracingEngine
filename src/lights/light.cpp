#include "lights/light.hpp"

Light::Light(const Vector &vec, const color_rgb &c) : _vec(vec), _color(c) {}

color_rgb Light::getColor() const
{
	return _color;
}
