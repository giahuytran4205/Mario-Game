#pragma once
#include "SFML/Audio.hpp"
#include "ECS.hpp"
using namespace sf;

enum Trackname {
	Background,
	EarnCoin,
	HitBlock,
	GetItem,
	NumTrack
};

class SoundComponent : public Component {
private:
	Sound m_sound;
	SoundBuffer& m_soundBuf;

public:
	SoundComponent(SoundBuffer& soundBuf);
	~SoundComponent();

	void play();
	void stop();
};