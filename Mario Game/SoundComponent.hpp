#pragma once
#include "SFML/Audio.hpp"
#include "ECS.hpp"
#include "SoundBufferManager.hpp"
using namespace sf;

class SoundComponent : public Component {
private:
	Sound m_sound;
	SoundBufferManager* m_soundBufManager;
	bool m_togglePlay;
	int m_currentTrack;
	int m_duration;

public:
	SoundComponent(bool loop = false);
	~SoundComponent();

	void update() override;
	void play(SoundTrack track, int duration = 0);
	void play();
	void pause();
	void stop();
	void clear();
	void setSoundBuf(const SoundBuffer& soundBuf);
	void setLoop(bool loop);

	// Set the volume of the sound. The volume is a value between 0 (mute) and 100 (maximum).
	// The default value for the volume is 100.
	// @param volume: Volume of the sound.
	void setVolume(float volume);
};