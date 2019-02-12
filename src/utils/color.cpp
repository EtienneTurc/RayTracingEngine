#include "utils/color.hpp"
#include <iostream>

color_rgb subbSynthese(const color_rgb obj, const color_rgb li)
{
	return {obj[0] * li[0] / 255, obj[1] * li[1] / 255, obj[2] * li[2] / 255};
}

color_rgb addSynthese(const color_rgb l1, const color_rgb l2)
{
	uint8_t p0 = (l1[0] + l2[0] > 255) ? 255 : (l1[0] + l2[0]);
	uint8_t p1 = (l1[1] + l2[1] > 255) ? 255 : (l1[1] + l2[1]);
	uint8_t p2 = (l1[2] + l2[2] > 255) ? 255 : (l1[2] + l2[2]);
	return {p0, p1, p2};
}

color_rgb
operator*(float lambda, const color_rgb col)
{
	if (lambda > 1 || lambda < 0)
	{
		// TODO excpetion
		return col;
	}
	return {col[0] * lambda, col[1] * lambda, col[2] * lambda};
}

color_rgb operator*(const color_rgb col, float lambda)
{
	return lambda * col;
}

std::ostream &operator<<(std::ostream &stream, const color_rgb &col)
{
	stream << '(' << unsigned(col[0]) << ',' << unsigned(col[1])
		   << ',' << unsigned(col[2])
		   << ')';
	return stream;
}
