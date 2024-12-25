#pragma once
#include <vector>
#include <string>
#include "TileSet.hpp"
#include "AnimationTrack.hpp"
using namespace std;

class AnimationType {
private:
	vector<AnimationTrack> m_anim;
	string m_path;

public:
	AnimationType();
	AnimationType(string filename);
	~AnimationType();

	const vector<AnimationTrack>& getAnim() const;
	const string& getAnimPath() const;
};