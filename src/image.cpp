#include "image.hpp"

void Image::save(std::string output_name)
{
	std::ofstream ofs(output_name.c_str(), std::ios::out | std::ios::binary);
	ofs << "P6\n"
		<< width << " " << height << "\n255\n";
	for (unsigned i = 0; i < width * height; ++i)
	{
		ofs << pixel_data[bytes_per_pixel * i + 0] << pixel_data[bytes_per_pixel * i + 1] << pixel_data[bytes_per_pixel * i + 2];
	}

	ofs.close();
}

void Image::setPixel(const color_rgb col, const int index)
{
	pixel_data[3 * index] = col[0];
	pixel_data[3 * index + 1] = col[1];
	pixel_data[3 * index + 2] = col[2];
}

std::vector<unsigned char> Image::getData()
{
	return pixel_data;
}

unsigned int Image::getHeight()
{
	return height;
}

unsigned int Image::getWidth()
{
	return width;
}

unsigned int Image::getBytesPerPixel()
{
	return bytes_per_pixel;
}
