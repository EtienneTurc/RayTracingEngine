#include <iostream>
#include "image.hpp"
#include <string>

int main(int argc, char const *argv[])
{
	std::cout << "hi\n";
	Image img(100, 100, 3);
	img.save("test_save.ppm");
	return 0;
}
