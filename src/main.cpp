#include "scene.hpp"

int main(int argc, char const *argv[])
{
	Vector nul(0, 0, 0);
	Vector front(1, 0, 0);
	Camera cam(nul, front, 1);

	Vector top_dir(0, 0, 1);
	Screen screen(200, 200, 0.02, top_dir);

	std::vector<Triangle> obj;
	Vector A(3, 4, 4);
	Vector B(3, -4, 4);
	Vector C(3, 0, -4);
	Triangle T(A, B, C, {255, 0, 0});
	Vector E(2, 2, 2);
	Vector F(2, -2, 2);
	Vector G(2, 0, -2);
	Triangle Ta(E, F, G, {0, 0, 255});
	obj.push_back(T);
	obj.push_back(Ta);

	color_rgb col = {255, 255, 255};
	Vector lu(0, 3, 3);
	Light l(lu, col);

	Scene scene(cam, screen, l, obj);

	scene.render();

	return 0;
}
