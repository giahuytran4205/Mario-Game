#pragma once
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "TileSet.hpp"
#include "SpriteRenderer.hpp"
#include <vector>
#include <map>
using namespace std;

class Animation : public Component {
private:
	Sprite& m_animSprite;
	vector<vector<Frame>> m_anim;
	int m_countdown;
	bool m_isPlay;
	int m_currentTrack;
	int m_currentIndex;

public:
	Animation();
	Animation(Sprite& sprite, const vector<vector<Frame>>& anim);
	Animation(SpriteRenderer& spriteRenderer, const vector<vector<Frame>>& anim);
	Animation(Sprite& sprite, int numTrack = 0);
	Animation(SpriteRenderer& spriteRenderer, int numTrack = 0);
	~Animation();

	void loadFromJsonFile(string filename);
	void update() override;
	void play(int track);
	void stop();
	void clear();
	int getCurrentTrack();
	bool isPlay();
	bool isPlayTrack(int track);
	void setAnim(int track, const vector<Frame>& anim);
};