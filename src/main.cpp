#include "utils/parser.hpp"
#include "utils/params.hpp"
#include <chrono>

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

	return 0;
}
