#pragma once
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"
#include "Mario.hpp"
#include "Block.hpp"

class EnemiesBuzzyBeetle : public Enemy {
public:
    enum State {
        NORMAL,     // Di chuyển bình thường
        STEP_2,     // Mai rùa đứng yên
        STEP_3      // Mai rùa di chuyển nhanh khi bị đá
    };

private:
    AutoControl& m_autoControl;
    SoundComponent& m_sound;
    float m_speed = -0.05f;
    int m_dir = 1;
    bool m_isDead = false;
    State mState = NORMAL;
    bool mIsStep2 = false;
    bool mIsStep3 = false;
    int mTimeUpdate = 0;

public:
    EnemiesBuzzyBeetle(Object* parent = nullptr);
    ~EnemiesBuzzyBeetle();
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void update() override;
    void hit(bool isDestroy);
    EnemiesBuzzyBeetle::State getState();
};
