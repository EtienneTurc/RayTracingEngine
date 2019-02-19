#include "objects/object.hpp"

Object::Object(const color_rgb &col, float transparency, float reflexivity) : _color(col), _transparency(transparency), _reflexivity(reflexivity) {}

color_rgb Object::getColor() const
{
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
