#include "Animation.hpp"
#include "Object.hpp"
#include <boost/json.hpp>
#include "GameManager.hpp"
namespace json = boost::json;

Animation::Animation() : m_animSprite(m_entity->getComponent<SpriteRenderer>().getSprite()), m_countdown(0), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1) {}

Animation::Animation(Sprite& sprite, const vector<vector<Frame>>& anim) : m_animSprite(sprite), m_anim(anim), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1), m_countdown(0) {}

Animation::Animation(SpriteRenderer& spriteRenderer, const vector<vector<Frame>>& anim) : Animation(spriteRenderer.getSprite(), anim) {}

Animation::Animation(Sprite& sprite, int numTrack) : m_animSprite(sprite), m_anim(numTrack), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1), m_countdown(0) {}

Animation::Animation(SpriteRenderer& spriteRenderer, int numTrack) : Animation(spriteRenderer.getSprite(), numTrack) {}

Animation::~Animation() {

}

void Animation::loadFromJsonFile(string filename) {
	json::object parsed = readJsonFile(filename);

	string imagePath = parsed["image"].as_string().c_str();
	int imagewidth = parsed["imagewidth"].as_int64();
	int imageheight = parsed["imageheight"].as_int64();
	int tilewidth = parsed["tilewidth"].as_int64();
	int tileheight = parsed["tileheight"].as_int64();
	int col = parsed["columns"].as_int64();
	int size = parsed["tiles"].as_array().size();

	m_anim.assign(size, {});
	Image tileset;
	tileset.loadFromFile(imagePath);

	for (auto& item : parsed["tiles"].as_array()) {
		json::object obj = item.as_object();
		
		int state = obj["properties"].as_array()[0].as_object()["value"].as_int64();
		for (auto& item : obj["animation"].as_array()) {
			json::object object = item.as_object();
			int id = object["tileid"].as_int64();
			int duration = object["duration"].as_int64();

			Frame frame;
			frame.texture = new Texture();
			frame.texture->loadFromImage(tileset, IntRect(id % col * tilewidth, id / col * tileheight, tilewidth, tileheight));
			frame.duration = duration;

			m_anim[state].push_back(frame);
		}
	}
}

void Animation::update() {
	if (m_currentTrack != -1 && isPlay()) {
		if (m_countdown > 0) m_countdown -= deltaTime.asMilliseconds();
		else {
			const Frame& frame = m_anim[m_currentTrack][++m_currentIndex % m_anim[m_currentTrack].size()];
			m_animSprite.setTexture(*frame.texture);
			m_countdown = frame.duration;
		}
	}
	
}

void Animation::play(int track) {
	if (m_currentTrack != track) m_currentIndex = -1;
	m_currentTrack = track;
	m_isPlay = true;
}

void Animation::stop() {
	m_isPlay = false;
}

void Animation::clear() {
	m_anim.clear();
}

int Animation::getCurrentTrack() {
	return m_currentTrack;
}

bool Animation::isPlay() {
	return m_isPlay;
}

bool Animation::isPlayTrack(int trackname) {
	return m_currentTrack == trackname && m_isPlay;
}

void Animation::setAnim(int trackname, const vector<Frame>& anim) {
	m_anim[trackname] = anim;
}