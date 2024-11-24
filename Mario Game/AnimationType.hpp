#pragma once
#include <vector>
#include <string>
#include "TileSet.hpp"
using namespace std;

class AnimationType {
private:
	vector<vector<Frame>> m_anim;
	string m_path;

public:
	AnimationType();
	AnimationType(string filename);
	~AnimationType();

	const vector<vector<Frame>>& getAnim() const;
	const string& getAnimPath() const;
};