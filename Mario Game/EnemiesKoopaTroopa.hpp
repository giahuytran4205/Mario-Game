#pragma once
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"
#include "Mario.hpp"
#include "Block.hpp"

class EnemiesKoopaTroopa : public Enemy {
public:
    enum State {
        NORMAL,     // Đi bộ bình thường
        STEP_2,     // Mai rùa đứng yên
        STEP_3      // Mai rùa di chuyển nhanh khi bị đá
    };

private:
    float m_speed = -0.05f;
    int m_dir = 1;
    bool m_isDead = false;
    State mState = NORMAL;
    bool mIsStep2 = false;
    bool mIsStep3 = false;
    int mTimeUpdate = 0;
    bool mIsCanFly{ false };
    int mLive{ 1 };

    float m_speedY = -0.2f;
    int m_dirY = 1;
public:
    EnemiesKoopaTroopa(Object* parent = nullptr, bool isCanFly = false);
    ~EnemiesKoopaTroopa();
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void update() override;
    void hit(bool isDestroy);
    EnemiesKoopaTroopa::State getState();
};
