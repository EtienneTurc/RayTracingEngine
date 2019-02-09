#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "utils/vector.hpp"
#include "utils/types.hpp"

class Light
{
  private:
	Vector _position;
	color_rgb _color;

  public:
	Light(Vector pos, color_rgb c);
	~Light() {}

	color_rgb getColor() const;
	Vector getPosition() const;
};

color_rgb subbSynthese(color_rgb obj, color_rgb li);

#endif //LIGHT_HPP
