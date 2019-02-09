#include "screen.hpp"

Screen::Screen(const unsigned h, const unsigned w, const float s, const Vector top_dir)
{
	_height = h;
	_width = w;
	_pixel_size = s;
	_data = std::vector<color_rgb>(h * w, {0, 0, 0});
	_top_dir = top_dir.normalize();
}

void Screen::setPixelColor(int row, int col, color_rgb color)
{
	_data[_height * col + row] = color;
}

unsigned Screen::getHeight() const
{
	return _height;
}

unsigned Screen::getWidth() const
{
	return _width;
}

float Screen::getPixelSize() const
{
	return _pixel_size;
}

Vector Screen::pixelDirection(const unsigned row, const unsigned col, const Vector center) const
{
	Vector _left_dir = center.crossProduct(_top_dir).normalize();
	float right_distance = row * _pixel_size + _pixel_size / 2 - _width * _pixel_size / 2;
	float bottom_distance = col * _pixel_size + _pixel_size / 2 - _height * _pixel_size / 2;
	Vector inner = _top_dir * (-bottom_distance) + _left_dir * (-right_distance);
	return inner + center;
}

void Screen::save(std::string output_name)
{
	std::ofstream ofs(output_name.c_str(), std::ios::out | std::ios::binary);
	ofs << "P6\n"
		<< _width << " " << _height << "\n255\n";
	for (unsigned i = 0; i < _width * _height; ++i)
	{
		ofs << _data[i][0] << _data[i][1] << _data[i][2];
	}

	ofs.close();
}
