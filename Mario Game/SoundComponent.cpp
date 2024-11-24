#include "SoundComponent.hpp"
#include "GameManager.hpp"
#include <iostream>

SoundComponent::SoundComponent(bool loop) : m_soundBufManager(SoundBufferManager::getInstance()), m_togglePlay(false), m_currentTrack(-1), m_duration(0) {
	m_sound.setLoop(loop);
}

SoundComponent::~SoundComponent() {}

void SoundComponent::update() {
	if (m_duration > 0)
		m_duration -= deltaTime.asMilliseconds();
}

void SoundComponent::play(SoundTrack track, int duration) {
	if (m_duration > 0)
		return;

	if (!m_soundBufManager)
		return;

	m_duration = duration;
	//m_sound.stop();
	m_sound.setBuffer(m_soundBufManager->getSoundBuf(track));
	m_sound.play();
}

void SoundComponent::play() {
	if (m_duration > 0) return;
	m_sound.play();
}

void SoundComponent::pause() {
	m_sound.pause();
}

void SoundComponent::stop() {
	m_sound.stop();
}

void SoundComponent::clear() {
	m_sound.resetBuffer();
	m_sound.stop();
}

void SoundComponent::setSoundBuf(const SoundBuffer& soundBuf) {
	m_sound.setBuffer(soundBuf);
}

void SoundComponent::setLoop(bool loop) {
	m_sound.setLoop(loop);
}

void SoundComponent::setVolume(float volume) {
	m_sound.setVolume(volume);
}