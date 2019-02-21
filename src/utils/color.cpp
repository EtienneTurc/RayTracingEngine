#include "utils/color.hpp"
#include <iostream>

color_rgb subbSynthese(const color_rgb &obj, const color_rgb &li)
{
	uint8_t r = (uint8_t)(obj[0] * li[0] / 255);
	uint8_t g = (uint8_t)(obj[1] * li[1] / 255);
	uint8_t b = (uint8_t)(obj[2] * li[2] / 255);
	return {r, g, b};
}

color_rgb addSynthese(const color_rgb &l1, const color_rgb &l2)
{
	uint8_t p0 = (l1[0] + l2[0] > 255) ? 255 : (l1[0] + l2[0]);
	uint8_t p1 = (l1[1] + l2[1] > 255) ? 255 : (l1[1] + l2[1]);
	uint8_t p2 = (l1[2] + l2[2] > 255) ? 255 : (l1[2] + l2[2]);
	return {p0, p1, p2};
}

color_rgb operator*(float lambda, const color_rgb &col)
{
	if (lambda > 1 || lambda < 0)
	{
		// TODO: exception
		return col;
	}
	return {(uint8_t)(col[0] * lambda), (uint8_t)(col[1] * lambda), (uint8_t)(col[2] * lambda)};
}

color_rgb operator*(const color_rgb &col, float lambda)
{
	return lambda * col;
}

color_rgb operator*(const color_rgb &col1, const color_rgb &col2)
{
	uint8_t r = (uint8_t)(col1[0] * col2[0] / 255);
	uint8_t g = (uint8_t)(col1[1] * col2[1] / 255);
	uint8_t b = (uint8_t)(col1[2] * col2[2] / 255);
	return {r, g, b};
}

color_rgb operator+(const color_rgb &col1, const color_rgb &col2)
{
	return addSynthese(col1, col2);
}

std::ostream &operator<<(std::ostream &stream, const color_rgb &col)
{
	stream << '(' << unsigned(col[0]) << ',' << unsigned(col[1])
		   << ',' << unsigned(col[2])
		   << ')';
	return stream;
}
