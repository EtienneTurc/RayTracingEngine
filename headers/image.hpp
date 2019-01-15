#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_
#include <vector>
#include <fstream>
#include <string>

class Image
{
  public:
	Image() {}
	Image(unsigned int w, unsigned int h, unsigned int bytes_per_pix) : height(h), width(w), bytes_per_pixel(bytes_per_pix), pixel_data(h * w * bytes_per_pix) {}
	~Image() {}

	void display();
	void save(std::string output_name);

  private:
	unsigned int height, width, bytes_per_pixel;
	std::vector<unsigned char> pixel_data;
};

#endif
