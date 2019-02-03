#include "object/face.hpp"

Face::Face(Point3d A, Point3d B, Point3d C) {
    _A = A;
    _B = B;
    _C = C;

    // Compute edges
	_U = _B - _A;
	_V = _C - _A;
	_W = _C - _B;

    _normal = prodVect(_U, _V); 
}

Face::Face(Point3d A, Point3d B, Point3d C, Vector3d n) {
    _A = A;
    _B = B;
    _C = C;

    // Compute edges
	_U = _B - _A;
	_V = _C - _A;
	_W = _C - _B;

    _normal = n; 
}

Point3d Face::getA() {
    return _A;
}
Point3d Face::getB() {
    return _B;
}
Point3d Face::getC() {
    return _C;
}
Vector3d Face::getNormal() {
    return _normal;
}