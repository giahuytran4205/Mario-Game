#include "AnimationFactory.hpp"
#include <algorithm>

vector<AnimationType> AnimationFactory::m_animTypes;

AnimationFactory::AnimationFactory() {}

AnimationFactory::~AnimationFactory() {}

AnimationType AnimationFactory::getFlyweight(string animName) {
	auto it = find_if(m_animTypes.begin(), m_animTypes.end(), [&animName](const AnimationType& type) { return type.getAnimPath() == animName; });
	if (it == m_animTypes.end()) {
		AnimationType res(animName);
		m_animTypes.push_back(res);
		return res;
	}
	return *it;
}