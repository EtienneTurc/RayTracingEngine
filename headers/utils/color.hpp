#ifndef _TYPE_HPP_
#define _TYPE_HPP_
#include <array>

typedef std::array<uint8_t, 3> color_rgb;

color_rgb subbSynthese(const color_rgb obj, const color_rgb li); // surfaces / lumière
color_rgb addSynthese(const color_rgb l1, const color_rgb l2);   //pour ajouter des lumières
color_rgb operator*(const color_rgb col, float lambda);
color_rgb operator*(float lambda, const color_rgb col);

#endif
