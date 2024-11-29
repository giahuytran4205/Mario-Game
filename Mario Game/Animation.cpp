#include "Animation.hpp"
#include "Object.hpp"
#include <boost/json.hpp>
#include "GameManager.hpp"
#include "AnimationFactory.hpp"
namespace json = boost::json;

Animation::Animation() : m_animSprite(m_entity->getComponent<SpriteRenderer>().getSprite()), m_countdown(0), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1) {}

Animation::Animation(string filename) : Animation() {
	loadFromJsonFile(filename);
}

Animation::Animation(Sprite& sprite, const vector<vector<Frame>>& anim) : m_animSprite(sprite), m_anim(anim), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1), m_countdown(0) {}

Animation::Animation(SpriteRenderer& spriteRenderer, const vector<vector<Frame>>& anim) : Animation(spriteRenderer.getSprite(), anim) {}

Animation::Animation(Sprite& sprite, int numTrack) : m_animSprite(sprite), m_anim(numTrack), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1), m_countdown(0) {}

Animation::Animation(SpriteRenderer& spriteRenderer, int numTrack) : Animation(spriteRenderer.getSprite(), numTrack) {}

Animation::~Animation() {

}

Animation& Animation::operator=(const Animation& anim) {
	m_anim = anim.m_anim;
	return *this;
}

void Animation::loadFromJsonFile(string filename) {
	m_anim = AnimationFactory::getFlyweight(filename).getAnim();
	m_animSprite.setTexture(m_anim[0][0].texture);
}

void Animation::update() {
	if (m_currentTrack != -1 && isPlay()) {
		if (m_countdown > 0) m_countdown -= deltaTime.asMilliseconds();
		else {
			const Frame& frame = m_anim[m_currentTrack][++m_currentIndex %= m_anim[m_currentTrack].size()];
			m_animSprite.setTexture(frame.texture);
			m_countdown += frame.duration;
		}
	}
	
}

void Animation::play(int track) {
	if (m_currentTrack != track) m_currentIndex = -1;
	m_currentTrack = track;
	m_isPlay = true;
}

void Animation::pause() {
	m_isPlay = false;
}

void Animation::stop() {
	m_isPlay = false;
	if (m_currentTrack != -1) m_animSprite.setTexture(m_anim[m_currentTrack][0].texture);
	m_currentTrack = -1;
}

void Animation::clear() {
	m_anim.clear();
}

int Animation::getCurrentTrack() {
	return m_currentTrack;
}

int Animation::getOffset() {
	int offset = 0;

	for (int i = 0; i < m_currentIndex - 1; i++) {
		offset += m_anim[m_currentTrack][i].duration;
	}

	offset += m_anim[m_currentTrack][m_currentIndex].duration - max(m_countdown, 0);
	return offset;
}

int Animation::getIndexInCurrentTrack() {
	return m_currentIndex;
}

int Animation::getTrackLength(int track) {
	int length = 0;

	for (auto& i : m_anim[track]) {
		length += i.duration;
	}

	return length;
}

bool Animation::isPlay() {
	return m_isPlay;
}

bool Animation::isPlayTrack(int trackname) {
	return m_currentTrack == trackname && m_isPlay;
}

void Animation::addAnim(const vector<Frame>& anim) {
	m_anim.push_back(anim);
}

void Animation::setAnim(int trackname, const vector<Frame>& anim) {
	m_anim[trackname] = anim;
}