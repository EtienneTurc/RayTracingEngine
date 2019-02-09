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

color_rgb subbSynthese(color_rgb obj, color_rgb li)
{
	return {obj[0] * li[0] / 255, obj[1] * li[1] / 255, obj[2] * li[2] / 255};
}
