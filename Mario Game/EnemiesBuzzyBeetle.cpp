#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesGoomba.hpp"
#include "EnemiesKoopaTroopa.hpp"

EnemiesBuzzyBeetle::EnemiesBuzzyBeetle(Object* parent) :
    Enemy(parent),
    m_autoControl(addComponent<AutoControl>()),
    m_sound(addComponent<SoundComponent>()) {
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/buzzy.json");
    m_anim.play(0);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0.5, 0.5);
}

EnemiesBuzzyBeetle::~EnemiesBuzzyBeetle() {
}
void EnemiesBuzzyBeetle::onCollisionEnter(Collision& col, const Direction& side) {
    if (m_isDead) {
        return;
    }

    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            m_sound.play(SoundTrack::STOMP);
            if (mState == NORMAL) {
                hit(true);
                m_transform.setSize(16, 16);
                mIsStep2 = true;
            }
            else if (mState == STEP_2) {
                mIsStep3 = true;
                m_dir = (col.m_entity->getComponent<Transform2D>().getPosition().x >
                    m_transform.getPosition().x) ? -1 : 1;
            }
            else if (mState == STEP_3) {
                mState = STEP_2;
                mTimeUpdate = 0;
            }
            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
        }
        else {
            if (mState == STEP_2) {
                mIsStep3 = true;
                if (side == Direction::LEFT) {
                    m_dir = 1;
                }
                else if (side == Direction::RIGHT) {
                    m_dir = -1;
                }
            }
            else if (mState == STEP_3 || mState == NORMAL) {
                col.m_entity->convertTo<Mario>()->dead();
            }
        }
    }
    else if (col.m_entity->isDerivedFrom<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            m_dir *= -1;
        }
    }
    else if (col.m_entity->isDerivedFrom<Enemy>()) {
        if (col.m_entity->isType<EnemiesBuzzyBeetle>()) {
            EnemiesBuzzyBeetle* otherBuzzy = col.m_entity->convertTo<EnemiesBuzzyBeetle>();

            if (mState == STEP_3) {
                if (otherBuzzy->getState() == NORMAL) {
                    otherBuzzy->hit(true);
                    col.m_entity->toObject()->destroy();
                }
                else if (otherBuzzy->getState() == STEP_3) {
                    mState = STEP_2;
                    otherBuzzy->mState = STEP_2;
                    mTimeUpdate = 0;
                    otherBuzzy->mTimeUpdate = 0;
                    m_physics.setBaseVelocityX(0);
                    otherBuzzy->getComponent<Physics2D>().setBaseVelocityX(0);
                }
            }
            else if (otherBuzzy->getState() == STEP_3) {
                hit(true);
                this->toObject()->destroy();
            }
            else {
                if (side == Direction::LEFT || side == Direction::RIGHT) {
                    m_dir *= -1;
                }
            }
        }
        else {
            if (mState == STEP_3) {
                col.m_entity->toObject()->destroy();
            }
            else {
                if (side == Direction::LEFT || side == Direction::RIGHT) {
                    m_dir *= -1;
                }
            }
        }
    }
}

void EnemiesBuzzyBeetle::update() {
    if (m_isDead) {
        return;
    }

    if (mState == NORMAL) {
        m_physics.setBaseVelocityX(m_speed * m_dir);
        if (m_dir < 0) {
            m_sprite.setScale(-1, 1);
        }
        else {
            m_sprite.setScale(1, 1);
        }
    }
    else if (mState == STEP_2) {
        m_physics.setBaseVelocityX(0);
        mTimeUpdate++;

        if (mTimeUpdate >= 200) {
            m_anim.play(2);
        }
        if (mTimeUpdate >= 300) {
            mState = NORMAL;
            m_transform.setSize(16, 16);  // Keep 16x16 size
            m_anim.loadFromJsonFile("Resources/Animations/buzzy.json");
            m_anim.play(0);
            mTimeUpdate = 0;
        }
    }
    else if (mState == STEP_3) {
        m_physics.setBaseVelocityX(m_speed * m_dir * 2);
    }

    if (mIsStep2) {
        m_transform.setSize(16, 16);
        m_anim.loadFromJsonFile("Resources/Animations/buzzy.json");
        m_anim.play(1);
        mTimeUpdate = 0;
        mIsStep2 = false;
        mState = STEP_2;
    }

    if (mIsStep3) {
        mState = STEP_3;
        mIsStep3 = false;
        mTimeUpdate = 0;
    }
}

void EnemiesBuzzyBeetle::hit(bool isDestroy) {
    if (isDestroy) {
        mState = STEP_2;
        m_anim.loadFromJsonFile("Resources/Animations/buzzy.json");
        m_anim.play(1);
    }
}

EnemiesBuzzyBeetle::State EnemiesBuzzyBeetle::getState() {
    return mState;
}
