#ifndef _GENERIC_OBJECT_HPP_
#define _GENERIC_OBJECT_HPP_

#include <fstream>
#include <algorithm>
#include <stdlib.h>

#include "object/object.hpp"
#include "object/face.hpp"

struct face_summit {
    unsigned summit;
    unsigned normal;
};



class GenericObject : public Object
{
  public:
	GenericObject(std::string filename, const float op, const color_rgb col);
	GenericObject(std::string filename, const float op, const color_rgb col, Vector3d translation);
	~GenericObject() {}

	float distance(const Point3d);
	Vector3d normal_at(const Point3d);

  private:
    std::vector<Face> _faces;

	void loaderObj(std::string, Vector3d);
	int getIndexClosestFace(Point3d);

};

#endif
