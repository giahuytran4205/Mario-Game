#pragma once
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <vector>
using namespace std;
using namespace sf;

enum class SoundTrack {
	BACKGROUND,
	BIGJUMP,
	HITBLOCK,
	ITEM,
	COIN,
	FLAGPOLE,
	WARP,
	NUM_TRACK
};

class SoundBufferManager {
private:
	vector<pair<SoundTrack, string>> soundPath = {
		{ SoundTrack::BACKGROUND,	"background.wav" },
		{ SoundTrack::BIGJUMP,		"Resources/Sounds/Big Jump.wav" },
		{ SoundTrack::HITBLOCK,		"" },
		{ SoundTrack::ITEM,			"Resources/Sounds/Item.wav" },
		{ SoundTrack::COIN,			"Resources/Sounds/Coin.wav" },
		{ SoundTrack::FLAGPOLE,		"Resources/Sounds/Flagpole.wav" },
		{ SoundTrack::WARP,			"Resources/Sounds/Warp.wav" }
	};

	vector<SoundBuffer> m_soundBufs;
	static SoundBufferManager* m_instance;

public:
	SoundBufferManager();
	~SoundBufferManager();

	const SoundBuffer& getSoundBuf(SoundTrack track);
	static SoundBufferManager* getInstance();
	int getSoundBufCount();
};