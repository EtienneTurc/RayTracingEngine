#include "light.hpp"

Light::Light(Vector pos, color_rgb c) : _position(pos), _color(c) {}

color_rgb Light::getColor() const
{
	return _color;
}

Vector Light::getPosition() const
{
	return _position;
}
