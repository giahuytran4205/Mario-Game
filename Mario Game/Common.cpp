#include "Common.hpp"
#include <iostream>
#include <fstream>
using namespace std;
namespace json = boost::json;

json::object readJsonFile(string filename) {
	ifstream fIn(filename);

	if (!fIn) {
		cerr << "Cannot open file!";
		return {};
	}

	string jsonContent((istreambuf_iterator<char>(fIn)), std::istreambuf_iterator<char>());

	json::value parsed = json::parse(jsonContent);
	return parsed.as_object();
}

Color darkenColor(const Color& color, float factor) {
	Color newColor;
	newColor.r = max(color.r - factor, 0.0f);
	newColor.g = max(color.g - factor, 0.0f);
	newColor.b = max(color.b - factor, 0.0f);
	newColor.a = max(color.a - factor, 0.0f);

	return newColor;
}