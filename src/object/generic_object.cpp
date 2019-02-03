#include "object/generic_object.hpp"

GenericObject::GenericObject(std::string filename, Vector3d translation, const float op, const color_rgb col) : Object(op, col)
{
    std::ifstream file("../../objects/cube.obj");

    std::cout << "in constructor\n";
    std::cout << file.is_open() << "\n";
    if (file.is_open())
    {
        std::string line;
        std::cout << "line\n";
        while (getline(file, line))
        {
            std::cout << line << '\n';
        }
    }
}

float GenericObject::distance(const Point3d pt)
{
}

Vector3d GenericObject::normal_at()
{
}