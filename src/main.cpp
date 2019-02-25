#include <chrono>

#include "utils/parser.hpp"
#include "utils/params.hpp"
#include "objects/triangle.hpp"
#include "utils/texture.hpp"

int main(int argc, char const *argv[])
{
	std::chrono::time_point<std::chrono::system_clock>
		start, end;
	start = std::chrono::system_clock::now();

	std::string path = "scene.json";
	if (argc == 2)
		path = argv[1];

	Scene scene = jsonToScene(path);

	scene.render();

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "Temps de calcul : " << elapsed_seconds.count()
			  << std::endl;

	return 0;
}
