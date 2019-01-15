#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>
#include "light/light.hpp"
#include "object/object.hpp"
#include "camera.hpp"

class Scene
{
  public:
	Scene(const Camera c) : _cam(c) {}
	// Scene(const Light l, const Object &object, const Camera c);
	// Scene(const std::vector<Light> l, const Object &object, const Camera c);
	// Scene(const Light l, const std::vector<Object> object, const Camera c);
	// Scene(const std::vector<Light> l, const std::vector<Object> object, const Camera c);
	~Scene() {}

	void addLigth(const Light light);

	void addObject(const Object new_object);

  private:
	std::vector<Light> _lights;
	std::vector<Object> _objects;
	Camera _cam;
};

#endif
