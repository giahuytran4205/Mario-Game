#pragma once
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include <vector>
using namespace std;
using namespace sf;

enum class SoundTrack {
	BACKGROUND,
	OVERWORLD,
	UNDERGROUND,
	CASTLE,
	UNDERWATER,
	BIGJUMP,
	ITEM,
	COIN,
	FLAGPOLE,
	FIREBALL,
	WARP,
	DIE,
	BREAK,
	BUMP,
	FIREWORK,
	ONE_UP,
	POWER_UP,
	PAUSE,
	STOMP,
	NUM_TRACK
};

class SoundBufferManager {
private:
	vector<pair<SoundTrack, string>> soundPath = {
		{ SoundTrack::BACKGROUND,	"Resources/Sounds/overworld.mp3" },
		{ SoundTrack::BIGJUMP,		"Resources/Sounds/jump-super.mp3" },
		{ SoundTrack::ITEM,			"Resources/Sounds/powerup-appears.mp3" },
		{ SoundTrack::COIN,			"Resources/Sounds/coin.mp3" },
		{ SoundTrack::FLAGPOLE,		"Resources/Sounds/flagpole.mp3" },
		{ SoundTrack::FIREBALL,		"Resources/Sounds/fireball.mp3" },
		{ SoundTrack::WARP,			"Resources/Sounds/pipe.mp3" },
		{ SoundTrack::DIE,			"Resources/Sounds/life-lost.mp3" },
		{ SoundTrack::BREAK,		"Resources/Sounds/breakblock.mp3" },
		{ SoundTrack::BUMP,			"Resources/Sounds/Bump.wav" },
		{ SoundTrack::FIREWORK,		"Resources/Sounds/fireworks.mp3" },
		{ SoundTrack::PAUSE,		"Resources/Sounds/pause.mp3" },
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