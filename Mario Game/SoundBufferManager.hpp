#pragma once
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <vector>
using namespace std;
using namespace sf;

enum class SoundTrack {
	BACKGROUND,
	BIGJUMP,
	ITEM,
	COIN,
	FLAGPOLE,
	WARP,
	DIE,
	BREAK,
	BUMP,
	NUM_TRACK
};

class SoundBufferManager {
private:
	vector<pair<SoundTrack, string>> soundPath = {
		{ SoundTrack::BACKGROUND,	"background.wav" },
		{ SoundTrack::BIGJUMP,		"Resources/Sounds/Big Jump.wav" },
		{ SoundTrack::ITEM,			"Resources/Sounds/Item.wav" },
		{ SoundTrack::COIN,			"Resources/Sounds/Coin.wav" },
		{ SoundTrack::FLAGPOLE,		"Resources/Sounds/Flagpole.wav" },
		{ SoundTrack::WARP,			"Resources/Sounds/Warp.wav" },
		{ SoundTrack::DIE,			"Resources/Sounds/Die.wav" },
		{ SoundTrack::BREAK,		"Resources/Sounds/Break.wav" },
		{ SoundTrack::BUMP,			"Resources/Sounds/BUMP.wav" }
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