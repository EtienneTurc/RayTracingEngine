#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <array>

#include "utils/color.hpp"

class texture
{
  private:
	/* data */
	unsigned _height;
	unsigned _width;
	std::vector<color_rgba> _data;

  public:
	texture(std::string filepath);
	~texture() {}

	color_rgba sample(float u, float v) const;
};

#endif // TEXTURE_HPP
