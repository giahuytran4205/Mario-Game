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