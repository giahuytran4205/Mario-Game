#include "EnemiesBuzzyBeetle.h"


EnemiesBuzzyBeetle::EnemiesBuzzyBeetle(Object* parent)
{
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);

}

EnemiesBuzzyBeetle::~EnemiesBuzzyBeetle()
{
}

void EnemiesBuzzyBeetle::onCollisionEnter(Collision& col, const Direction& side)
{
    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            if (mIsStep2 == false) {
                mIsStep2 = true;

            }
            else if (mState == STEP_2) {
                mIsStep3 = true;
            }

        }
    }
    else {
        if (col.m_entity->isType<Block>()) {
            if (side == Direction::LEFT || side == Direction::RIGHT) {
                m_onWall = true;
            }
        }
    }
}

void EnemiesBuzzyBeetle::hit(bool isDestroy)
{
}

void EnemiesBuzzyBeetle::update()
{
    if (m_onWall) {
        m_speed = -m_speed;
        m_onWall = false;
    }
    auto lastPost = m_transform.getLastPosition();
    if (lastPost.y < 430) {
        m_speed_Vy += G * deltaTime.asMilliseconds();
    }
    else {
        m_speed_Vy = 0;
    }

    if (mIsStep2) {
        m_anim.loadFromJsonFile("Resources/Animations/Fireball.json");
        mTimeUpdate = 0;
        mIsStep2 = false;
        mState = STEP_2;
    }
    if (mState == STEP_2) {
        m_transform.move(0, 0);
    }
    else {
        m_transform.move(m_speed, 0);
    }
    if (mIsStep3) {
        mState = STEP_3;
        mIsStep3 = false;
        mTimeUpdate = 0;
    }

    if (mState == STEP_3) {
        m_transform.move(m_speed*10, 0);
        if (mTimeUpdate > 200) {
            mState = STEP_2;
        }
    }
    mTimeUpdate++;

}

EnemiesBuzzyBeetle::State EnemiesBuzzyBeetle::getState()
{
    return mState;
}
