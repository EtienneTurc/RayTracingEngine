#include "scene.hpp"

// Scene::Scene(const Light l, const Object &object, const Camera c)
// {
// 	_lights.push_back(l);
// 	_objects.push_back(object);
// 	_cam = c;
// }

// Scene::Scene(const std::vector<Light> l, const Object &object, const Camera c)
// {
// 	_lights = l;
// 	_objects.push_back(object);
// 	_cam = c;
// }

// Scene::Scene(const Light l, const std::vector<Object> object, const Camera c)
// {
// 	_lights.push_back(l);
// 	_objects = object;
// 	_cam = c;
// }

// Scene::Scene(const std::vector<Light> l, const std::vector<Object> object, const Camera c)
// {
// 	_lights = l;
// 	_objects = object;
// 	_cam = c;
// }

void Scene::addLigth(const Light new_light)
{
	_lights.push_back(new_light);
}
