#ifndef FACE_HPP_
#define FACE_HPP_

#include <fstream>

#include "utils/point3d.hpp"
#include "utils/vector3d.hpp"
#include "type.hpp"

class Face
{
  public:
    Face(Point3d A, Point3d B, Point3d C);
    Face(Point3d A, Point3d B, Point3d C, Vector3d normal);
    ~Face(){}

    Point3d getA();
    Point3d getB();
    Point3d getC();
    Vector3d getNormal();
	
  private:
	Point3d _A;
	Point3d _B;
	Point3d _C;

    Vector3d _U;
    Vector3d _V;
    Vector3d _W;

    Vector3d _normal;

};

#endif