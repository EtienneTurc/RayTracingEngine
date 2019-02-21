#include <fstream>
#include <sstream>

#include "utils/loader_obj.hpp"
#include "objects/triangle.hpp"

std::vector<Object *> loaderObj(std::string filename, const color_rgb &col, const Vector &translation, const Vector &rotation, const Vector &mag)
{
	std::vector<Object *> objects;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string line;
		// std::vector<Triangle *> objects;
		float X = 0, Y = 0, Z = 0;
		std::vector<Vector> summits;
		while (getline(file, line))
		{
			std::string type = line.substr(0, 2);
			if (type == "v ")
			{
				std::istringstream v(line.substr(2));
				float x, y, z;
				v >> x;
				v >> y;
				v >> z;
				summits.push_back(Vector(x, y, z));
				X += x;
				Y += y;
				Z += z;
			}
			else if (type == "f ")
			{
				// std::cout << "f\n";
				std::vector<unsigned> index_summits;
				std::string sub_line = line.substr(1);
				while (sub_line.length() > 1)
				{
					unsigned index_value;
					const char *chh = sub_line.c_str();
					sscanf(chh, " %d/", &index_value);
					index_summits.push_back(index_value);
					unsigned i = 1;
					if (sub_line[i] == ' ')
					{
						++i;
					}

					while (sub_line[i] != ' ' && i < sub_line.length() - 1)
					{
						++i;
					}

					sub_line = sub_line.substr(i);
				}

				Vector barycenter(X / summits.size(), Y / summits.size(), Z / summits.size());

				//create triangle
				for (unsigned i = 1; i < index_summits.size() - 1; ++i)
				{
					Vector a = summits[index_summits[0] - 1];
					a = (a - barycenter).rotate3D(rotation).magnify(mag) + translation + barycenter;
					Vector b = summits[index_summits[i] - 1];
					b = (b - barycenter).rotate3D(rotation).magnify(mag) + translation + barycenter;
					Vector c = summits[index_summits[i + 1] - 1];
					c = (c - barycenter).rotate3D(rotation).magnify(mag) + translation + barycenter;
					Triangle *t = new Triangle(a, b, c, col, 0, 0);
					objects.push_back(t);
				}
			}
		}
		return objects;
	}
	else
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(-1);
	}
}
