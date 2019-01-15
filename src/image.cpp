#include "image.hpp"

void Image::save(std::string output_name)
{
    std::ofstream ofs( output_name.c_str(), std::ios::out | std::ios::binary );
    ofs << "P6\n"
        << width << " " << height << "\n255\n";
    for ( unsigned i = 0; i < width * height; ++i ) {
        ofs << pixel_data[ bytes_per_pixel * i + 0 ] << pixel_data[ bytes_per_pixel * i + 1 ] << pixel_data[ bytes_per_pixel * i + 2 ];
    }
    ofs.close();
}