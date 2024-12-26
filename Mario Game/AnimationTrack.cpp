#include "AnimationTrack.hpp"

bool AnimationTrack::hasExitTime() const {
    return m_hasExitTime;
}

bool AnimationTrack::isLoop() const {
    return m_isLoop;
}

int AnimationTrack::getExitTime() const {
    return m_exitTime;
}
 
void AnimationTrack::setEnableExitTime(bool isEnable) {
    m_hasExitTime = isEnable;
} 

void AnimationTrack::setExitTime(float time) {
    m_exitTime = time;
}

void AnimationTrack::setLoop(bool isLoop) {
    m_isLoop = isLoop;
}

std::vector<Frame>& AnimationTrack::getFrames() {
    return m_frames;
}

Frame& AnimationTrack::operator[](const int index) {
    return m_frames[index];
} 