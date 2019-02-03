#include "object/generic_object.hpp"

GenericObject::GenericObject(std::string filename, const float op, const color_rgb col) : Object(op, col)
{
    loaderObj(filename, Vector3d(0));
}

GenericObject::GenericObject(std::string filename, const float op, const color_rgb col, Vector3d translation): Object(op, col) {
    loaderObj(filename, translation);
}

void GenericObject::loaderObj(std::string filename, Vector3d translation) {
    std::ifstream file("objects/cube.obj");
    if (file.is_open())
    {
        std::string line;
        std::vector<Point3d> summits;
        std::vector<Vector3d> normals;
        while (getline(file, line))
        {
            std::string type = line.substr(0,2);
            if (type == "v ") {
                std::istringstream v(line.substr(2));
                float x, y, z;
                v>>x; v>>y; v>>z;
                summits.push_back(Point3d(x, y, z) + translation);
            }
            else if (type == "vn") {
                std::istringstream v(line.substr(2));
                float x, y, z;
                v>>x; v>>y; v>>z;
                normals.push_back(Vector3d(x, y, z));
            }
            else if (type == "vn") {
                unsigned int summitIndex[3], normalIndex[3];
                const char* chh = line.c_str();
                sscanf (chh, "f %d//%d %d//%d %d//%d\n", &summitIndex[0], &normalIndex[0],
                                                        &summitIndex[1], &normalIndex[1],
                                                        &summitIndex[2], &normalIndex[2] );

                // Create a new face
                _faces.push_back(Face(summits[summitIndex[0]-1],
                            summits[summitIndex[1]-1],
                            summits[summitIndex[2]-1],
                            normals[normalIndex[0]-1]
                ));
            }
            std::cout << line << '\n';
        }
    }
    else {
        std::cerr << "Cannot open " << filename << std::endl;
        exit(-1);
    }
}

float GenericObject::distance(const Point3d pt)
{   
    int min_index = getIndexClosestFace(pt);

}

int GenericObject::getIndexClosestFace(Point3d pt) {
    float d_min = 999999999;
    unsigned index_min = 0;
    for(size_t i = 0; i < _faces.size(); i++)
    {
        Face face = _faces[i];
        float new_dist = abs(
            face.getA().x + face.getA().y + face.getA().z + 
            face.getB().x + face.getB().y + face.getB().z + 
            face.getC().x + face.getC().y + face.getC().z
            -(pt.x + pt.y + pt.z)*3);
        if (d_min >= new_dist) {
            d_min = new_dist;
            index_min = i;
        }
    }
    if (d_min == 999999999) {
        return -1;
    }
    else return index_min;
    
}

Vector3d GenericObject::normal_at(Point3d pt)
{   //point sur la face => compute trouver la face puis donner la normale
    int min_index = getIndexClosestFace(pt);
    return _faces[min_index].getNormal();
}
