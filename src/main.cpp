#include "scene.hpp"
#include <chrono>

int main(int argc, char const *argv[])
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	Vector nul(0, 0, 0);
	Vector front(1, 0, 0);
	Camera cam(nul, front, 1);

	Vector top_dir(0, 0, 1);
	Screen screen(2000, 2000, 0.002, top_dir);

	std::vector<Triangle> obj;
	// Vector A1(3, 4, 4);
	// Vector B1(3, -4, 4);
	// Vector C1(3, 0, -4);
	// Triangle T1(A1, B1, C1, {255, 0, 0});
	// Vector A2(2, 1, 2);
	// Vector B2(2, -1, 2);
	// Vector C2(2, 0, -2);
	// Triangle T2(A2, B2, C2, {0, 0, 100});
	Vector A3(10000, 10000, -5);
	Vector B3(10000, -10000, -5);
	Vector C3(-10000, 0, -5);
	Triangle T3(A3, B3, C3, {50, 50, 50});
	obj.push_back(T3);
	// obj.push_back(T1);
	// obj.push_back(T2);

	std::vector<Light> lights;
	color_rgb col = {255, 255, 255};
	Vector l1(0, 0, 0);
	Light L1(l1, col);
	Vector l2(0, 3, 3);
	col = {250, 250, 250};
	Light L2(l2, col);
	lights.push_back(L2);
	lights.push_back(L1);

	Scene scene(cam, screen, lights, obj);
	Vector tr(4, -1, 0);
	Vector rot(90, 0, 0);
	// scene.loaderObj("./objects/two_triangle.obj", {255, 0, 0}, tr, nul);
	// scene.loaderObj("./objects/basic_triangle.obj", {255, 0, 0}, tr, nul);
	scene.loaderObj("./objects/sphere2.obj", {255, 0, 0}, tr, nul);

	std::cout << "Scene loaded\nRay tracing in progress\n";

	scene.render();

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Temps calcul ensemble mandelbrot : " << elapsed_seconds.count()
			  << std::endl;

	return 0;
}
