#include "object.hpp"

Object::Object(const color_rgb col, const float transparency) : _color(col), _transparency(transparency) {}

color_rgb Object::getColor() const
{
	return _color;
}

float Object::getTransparency() const
{
	return _transparency;
}
