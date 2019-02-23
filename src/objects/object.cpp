#include "objects/object.hpp"

Object::Object(const color_rgba &col, float transparency, float reflexivity) : _color(col), _transparency(transparency), _reflexivity(reflexivity) {}

color_rgba Object::getColor(const Vector &)
{
	_color[3] = 255;
	return _color;
}

float Object::getTransparency() const
{
	return _transparency;
}

float Object::getReflexivity() const
{
	return _reflexivity;
}
