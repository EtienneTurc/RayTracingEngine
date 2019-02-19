#include <fstream>
#include <streambuf>
#include <sstream>
#include <math.h>
#include "utils/json11.hpp"

#include "utils/parser.hpp"
#include "utils/loader_obj.hpp"

using namespace json11;
using namespace std;

Vector stringToVector(string str)
{
	stringstream ss(str);
	float x, y, z;
	ss >> x >> y >> z;
	Vector v(x, y, z);
	return v;
}

color_rgb stringToColor(string str)
{
	stringstream ss(str);
	float r, g, b;
	ss >> r >> g >> b;
	color_rgb color = {r, g, b};
	return color;
}

vec2 stringToVec2(string str)
{
	stringstream ss(str);
	float x, y;
	ss >> x >> y;
	vec2 v = {x, y};
	return v;
}

Scene jsonToScene(string path)
{
	ifstream t(path);
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	string err;
	Json scene_json = Json::parse(str, err);

	Json::array lights_json = scene_json["lights"].array_items();

	std::vector<Light> lights;
	for (int i = 0; i < lights_json.size(); i++)
	{
		string type = lights_json[i]["type"].string_value();
		if (type == "spot")
		{
			Vector position = stringToVector(lights_json[i]["position"].string_value());

			color_rgb color = stringToColor(lights_json[i]["color"].string_value());

			Light L(position, color);
			lights.push_back(L);
		}
	}

	Json::array objects_json = scene_json["objects"].array_items();

	std::vector<Object *> obj;
	for (int i = 0; i < objects_json.size(); i++)
	{
		string type = objects_json[i]["type"].string_value();
		if (type == "triangle")
		{
			Json::array positions = objects_json[i]["positions"].array_items();

			if (positions.size() != 3)
				continue;
			Vector A = stringToVector(positions[0].string_value());
			Vector B = stringToVector(positions[1].string_value());
			Vector C = stringToVector(positions[2].string_value());

			color_rgb color = stringToColor(objects_json[i]["color"].string_value());

			float transparency = objects_json[i]["transparency"].number_value();
			float reflexitivity = objects_json[i]["reflexitivity"].number_value();

			Triangle *T = new Triangle(A, B, C, color, transparency, reflexitivity);
			obj.push_back(T);
		}
	}

	// Vector tr(0, 0, 0);
	// // Vector rot(M_PI / 2, 0, M_PI / 2);
	// Vector rot(0, 0, 0);
	// Vector mag(1, 1, 1);
	// obj = loaderObj("./objects/chair.obj", {50, 50, 255}, tr, rot, mag);

	// Camera
	Json camera_json = scene_json["camera"];

	Vector camera_pos = stringToVector(camera_json["position"].string_value());
	Vector camera_dir = stringToVector(camera_json["direction"].string_value());
	float camera_dist = camera_json["dist_normal"].number_value();

	Camera cam(camera_pos, camera_dir, camera_dist);

	// Engine
	Json engine_json = scene_json["engine"];

	unsigned height = engine_json["screen_height"].int_value();
	unsigned width = engine_json["screen_width"].int_value();
	float pixel_size = engine_json["pixel_size"].number_value();
	Vector top_dir = stringToVector(engine_json["top_dir"].string_value());

	Json::array pixels_offset_json = engine_json["pixels_offset"].array_items();

	std::vector<vec2> pixels_offset;
	for (int i = 0; i < pixels_offset_json.size(); i++)
	{
		pixels_offset.push_back(stringToVec2(pixels_offset_json[i].string_value()));
	}

	Screen screen(height, width, pixel_size, top_dir, pixels_offset);

	Scene scene(cam, screen, lights, obj);
	return scene;
}
