#include "camera.hpp"

void Camera::move(const Point3d &pos)
{
	// Calcul en polaire de la position de la camera :
	position = pos;
}
