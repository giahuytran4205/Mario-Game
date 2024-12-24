#include "Animation.hpp"
#include "Object.hpp"
#include <boost/json.hpp>
#include "GameManager.hpp"
#include "AnimationFactory.hpp"
namespace json = boost::json;

Animation::Animation(Sprite& sprite) : m_animSprite(sprite), m_isPlay(false), m_currentTrack(-1), m_currentIndex(-1), m_countdown(0), m_exitTime(0) {}

Animation::Animation(Sprite& sprite, string filename) : Animation(sprite) {
	loadFromJsonFile(filename);
}

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
	if (m_exitTime > 0)
		m_exitTime -= deltaTime.asMilliseconds();

	if (m_currentTrack != -1 && isPlay()) {
		if (m_countdown > 0) m_countdown -= deltaTime.asMilliseconds();
		else {
			m_currentIndex++;
			if (m_currentIndex >= m_anim[m_currentTrack].getFrames().size()) {
				if (m_anim[m_currentTrack].isLoop())
					m_currentIndex = 0;
				else {
					m_currentIndex--;
					if (m_anim[m_currentTrack].hasExitTime()) {
						m_exitTime = m_anim[m_currentTrack].getExitTime();
						pause();
					}
				}
			}
			if (m_exitTime <= 0) {
				const Frame& frame = m_anim[m_currentTrack][m_currentIndex];
				m_animSprite.setTexture(frame.texture, true);
				m_countdown += frame.duration;
			}
		}
	}
	
}

void Animation::play(int track) {
	if (m_currentTrack != track) {
		if (m_currentTrack != -1 && m_anim[m_currentTrack].hasExitTime() && isPlay())
			return;

		m_currentIndex = -1;
	}

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

	for (auto& i : m_anim[track].getFrames()) {
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

AnimationTrack& Animation::getTrack(int track) {
	return m_anim[track];
}