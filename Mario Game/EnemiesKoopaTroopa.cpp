#include "EnemiesKoopaTroopa.h"

EnemiesKoopaTroopa::EnemiesKoopaTroopa( Object* parent)
{
	//m_transform.setSize(16, 16);
	//m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0.5, 0.5);
    //m_physics2D.setBaseVelocityX(m_speed);
}

EnemiesKoopaTroopa::~EnemiesKoopaTroopa()
{
}

void EnemiesKoopaTroopa::onCollisionEnter(Collision& col, const Direction& side)
{
    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            if (mIsStep2 == false) {
                mIsStep2 = true;

            }
            else if(mState == STEP_2){
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

void EnemiesKoopaTroopa::hit(bool isDestroy)
{
}

void EnemiesKoopaTroopa::update()
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
    mTimeUpdate++;
    if (mTimeUpdate >= 200 && mState == STEP_2 ) {
        mState = NORMAL;;
        m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
    }
    if (mIsStep3) {
        mIsStep3 = false;
        mTimeUpdate = 0;
        mState = STEP_3;
		
    }

    if (mTimeUpdate < 2000 && mState == STEP_3) {
        m_transform.move(m_speed * 10, m_speed_Vy);
    }
    else {
        m_transform.move(m_speed, m_speed_Vy); 
    }

}

EnemiesKoopaTroopa::State EnemiesKoopaTroopa::getState()
{
    return mState;
}

