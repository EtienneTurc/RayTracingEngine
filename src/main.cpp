#include <chrono>

#include "utils/parser.hpp"
#include "utils/params.hpp"
#include "objects/triangle.hpp"
#include "utils/texture.hpp"

int main()
{

	std::chrono::time_point<std::chrono::system_clock>
		start, end;
	start = std::chrono::system_clock::now();

	Scene scene = jsonToScene("scene.json");
	// scene.loaderObj("./objects/chair.obj", {150, 150, 150}, tr, rot, mag);

	scene.render();

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Temps de calcul : " << elapsed_seconds.count()
			  << std::endl;

	// Vector A(2, -2, 2);
	// Vector B(2, -2, -1);
	// Vector C(2, 1, -1);

	// uv A_uv = {0, 1};
	// uv B_uv = {0, 0};
	// uv C_uv = {1, 0};

	// texture *tex = new texture("test.png");

	// Triangle T(A, B, C, A_uv, B_uv, C_uv, tex, 0, 0);

	// Vector v(2, -1, 0);
	// color_rgba col = T.getColor(v);

	// std::cout << "Color : " << col << '\n';
	// std::cout << "Alpha : " << col[3] << '\n';

	return 0;
}
