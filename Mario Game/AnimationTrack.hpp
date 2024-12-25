#pragma once
#include <vector>
#include "TileSet.hpp"
using namespace std;

class AnimationTrack {
private:
	vector<Frame> m_frames;
	bool m_hasExitTime = false;
	int m_exitTime = 0;
	bool m_isLoop = true;

public:
	bool hasExitTime() const;
	bool isLoop() const;
	int getExitTime() const;
	void setEnableExitTime(bool isEnable);
	void setExitTime(float time);
	void setLoop(bool isLoop);
	vector<Frame>& getFrames();

	Frame& operator[](const int index);
};
