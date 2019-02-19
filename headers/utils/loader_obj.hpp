#ifndef LOADER_OBJ_HPP
#define LOADER_OBJ_HPP

#include <vector>

#include "objects/object.hpp"

std::vector<Object *> loaderObj(std::string filename, const color_rgb &col, const Vector &translation, const Vector &rotation, const Vector &mag);

#endif //LOADER_OBJ_HPP
