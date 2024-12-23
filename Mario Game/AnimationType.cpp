#include "AnimationType.hpp"
#include "Common.hpp"
#include "TextureManager.hpp"

AnimationType::AnimationType() {

}

AnimationType::AnimationType(string filename) {
	m_path = filename;

	json::object parsed = readJsonFile(filename);

	string imagePath = parsed["image"].as_string().c_str();
	int imagewidth = parsed["imagewidth"].as_int64();
	int imageheight = parsed["imageheight"].as_int64();
	int tilewidth = parsed["tilewidth"].as_int64();
	int tileheight = parsed["tileheight"].as_int64();
	int col = parsed["columns"].as_int64();
	//int size = parsed["tiles"].as_array().size();
	int size = 10;

	m_anim.assign(size, {});

	for (auto& item : parsed["tiles"].as_array()) {
		json::object obj = item.as_object();

		int state = obj["properties"].as_array()[0].as_object()["value"].as_int64();
		for (auto& item : obj["animation"].as_array()) {
			json::object object = item.as_object();
			int id = object["tileid"].as_int64();
			int duration = object["duration"].as_int64();

			Frame frame;
			frame.texture = TextureManager::getTile(imagePath, IntRect(id % col * tilewidth, id / col * tileheight, tilewidth, tileheight));
			frame.duration = duration;

			m_anim[state].push_back(frame);
		}
	}
}

AnimationType::~AnimationType() {

}

const vector<vector<Frame>>& AnimationType::getAnim() const {
	return m_anim;
}

const string& AnimationType::getAnimPath() const {
	return m_path;
}