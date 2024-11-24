#include "SoundBufferManager.hpp"

SoundBufferManager* SoundBufferManager::m_instance = nullptr;

SoundBufferManager::SoundBufferManager() : m_soundBufs((int)SoundTrack::NUM_TRACK) {
	if (m_instance) return;
	m_instance = this;

	for (auto& p : soundPath) {
		m_soundBufs[(int)p.first].loadFromFile(p.second);
	}
}

SoundBufferManager::~SoundBufferManager() {}

const SoundBuffer& SoundBufferManager::getSoundBuf(SoundTrack track) {
	return m_soundBufs[(int)track];
}

SoundBufferManager* SoundBufferManager::getInstance() {
	return m_instance;
}

int SoundBufferManager::getSoundBufCount() {
	return m_soundBufs.size();
}