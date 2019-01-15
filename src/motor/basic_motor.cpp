#include "basic_motor.hpp"
#include <algorythm>

void BasicMotor::render()
{
    std::fill (img.pixel_data.begin(), img.pixel_data.end(), 0);

    for ( unsigned y = 0; y < img.height; ++y ) {
        for ( unsigned x = 0; x < img.width; ++x ) {
            color_rgb color = trace(scene.objectif.position, x, y);
            img.set_color(img.height-y-1, x, col);
        }
    }
    
}

color_rgb BasicMotor::trace(const point3d& origin_pt)
{
    return 0;
}