#include "light.hpp"

Light::Light(const Vector &pos, const color_rgb &c) : _position(pos), _color(c) {}

color_rgb Light::getColor() const
{
	return _color;
}

Vector Light::getPosition() const
{
	return _position;
}
