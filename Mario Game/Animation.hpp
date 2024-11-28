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
	Animation(Sprite& sprite, string filename);
	Animation(Sprite& sprite, const vector<vector<Frame>>& anim = {});
	Animation(SpriteRenderer& spriteRenderer, const vector<vector<Frame>>& anim = {});
	Animation(Sprite& sprite, int numTrack);
	Animation(SpriteRenderer& spriteRenderer, int numTrack);
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
	void addAnim(const vector<Frame>& anim);
	void setAnim(int track, const vector<Frame>& anim);
};