#include "scene.hpp"

int main(int argc, char const *argv[])
{
	Vector nul(0, 0, 0);
	Vector front(1, 0, 0);
	Camera cam(nul, front, 1);

	Vector top_dir(0, 0, 1);
	Screen screen(200, 200, 0.02, top_dir);

	std::vector<Triangle> obj;
	Vector A(2, 4, 4);
	Vector B(2, -4, 4);
	Vector C(2, 0, -4);
	Triangle T(A, B, C, {255, 0, 0});
	obj.push_back(T);

	color_rgb col = {255, 255, 255};
	Light l(nul, col);

	Scene scene(cam, screen, l, obj);

	scene.render();

	return 0;
}
