#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <vector>
#include <fstream>

#include "utils/vector.hpp"
#include "utils/color.hpp"

class Screen
{
  private:
	unsigned _height, _width;
	float _pixel_size;
	Vector _top_dir;
	std::vector<color_rgb> _data;

  public:
	Screen(const unsigned h, const unsigned w, const float s, const Vector top_dir);
	~Screen() {}

	unsigned getHeight() const;
	unsigned getWidth() const;
	float getPixelSize() const;

	color_rgb operator()(int row, int col) const
	{
		return _data[_height * col + row];
	};
	Vector pixelDirection(const unsigned row, const unsigned col, const Vector center) const;
	void setPixelColor(int row, int col, color_rgb color);
	void save(std::string output_name);
};

#endif //SCREEN_HPP
