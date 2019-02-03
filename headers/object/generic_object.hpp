#ifndef _GENERIC_OBJECT_HPP_
#define _GENERIC_OBJECT_HPP_

#include <fstream>

#include "object/object.hpp"

struct face_summit {
    unsigned summit;
    unsigned texture;
    unsigned normal;
};



class GenericObject : public Object
{
  public:
	GenericObject(std::string filename, Vector3d translation, const float op, const color_rgb col);
	~GenericObject() {}

	float distance(const Point3d pt);
	Vector3d normal_at();

  private:
	std::vector<Point3d> summits;
    std::vector<Vector3d> normals;
    std::vector<float> textures;
    std::vector<std::array<face_summit, 3>> face;
};

#endif
