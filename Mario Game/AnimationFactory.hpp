#pragma once
#include <vector>
#include "AnimationType.hpp"

class AnimationFactory {
private:
	static vector<AnimationType> m_animTypes;

public:
	AnimationFactory();
	~AnimationFactory();

	static AnimationType getFlyweight(string animName);
};