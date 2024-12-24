#pragma once
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "TileSet.hpp"
#include "SpriteRenderer.hpp"
#include "AnimationTrack.hpp"
#include <vector>
#include <map>
using namespace std;

class Animation : public Component {
private:
	Sprite& m_animSprite;
	vector<AnimationTrack> m_anim;
	int m_countdown;
	int m_exitTime;
	bool m_isPlay;
	int m_currentTrack;
	int m_currentIndex;

public:
	Animation(Sprite& sprite);
	Animation(Sprite& sprite, string filename);
	~Animation();

	Animation& operator=(const Animation& anim);

	void loadFromJsonFile(string filename);
	void update() override;
	void play(int track);
	void pause();
	void stop();
	void clear();
	int getCurrentTrack();
	int getTrackLength(int track);
	int getOffset();
	int getIndexInCurrentTrack();
	bool isPlay();
	bool isPlayTrack(int track);
	AnimationTrack& getTrack(int track);
};