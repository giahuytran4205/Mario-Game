#include "EnemiesKoopaTroopa.hpp"


EnemiesKoopaTroopa::EnemiesKoopaTroopa(Object* parent, bool isCanFly):
    Enemy(parent), mIsCanFly(isCanFly)
{
   
    if (mIsCanFly) {
        mLive = 2;
        m_transform.setSize(16, 16);
        m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
    }
    else {
        mLive = 1;
        m_transform.setSize(16, 24);
        m_anim.loadFromJsonFile("Resources/Animations/koopa.json");
    }
   
    m_anim.play(0);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0.5, 0.5);
    m_physics.setEnableGravity(true);

}

EnemiesKoopaTroopa::~EnemiesKoopaTroopa() {
}

void EnemiesKoopaTroopa::onCollisionEnter(Collision& col, const Direction& side) {
    if (m_isDead) {
        return;
    }
    if (col.m_entity->isDerivedFrom<Projectile>()) {
        destroy();
    }

    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            m_sound.play(SoundTrack::STOMP);
            if (mState == NORMAL) {
                mLive--;
                if (mLive <=  0) {
                    hit(true);
                    m_transform.setSize(16, 16);
                    mIsStep2 = true;
                }
                else {
                    m_transform.setSize(16, 24);
                    m_anim.loadFromJsonFile("Resources/Animations/koopa.json");
                }

            }
            else if (mState == STEP_2) {
                mIsStep3 = true;
                m_dir = (col.m_entity->getComponent<Transform2D>().getPosition().x > m_transform.getPosition().x) ? -1 : 1;
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
        // Luôn giữ collision với Block để không rơi xuyên đất
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            m_dir *= -1;
        }
    }
    else if (col.m_entity->isDerivedFrom<Enemy>()) {
        if (col.m_entity->isType<EnemiesKoopaTroopa>()) {
            EnemiesKoopaTroopa* otherKoopa = col.m_entity->convertTo<EnemiesKoopaTroopa>();

            // Xử lý va chạm giữa 2 koopa
            if (mState == STEP_3) {
                // Nếu shell đang di chuyển va chạm với koopa bình thường
                if (otherKoopa->getState() == NORMAL) {
                    otherKoopa->hit(true);
                    col.m_entity->toObject()->destroy();
                }
                // Nếu 2 shell đang di chuyển va chạm với nhau
                else if (otherKoopa->getState() == STEP_3) {
                    mState = STEP_2;
                    otherKoopa->mState = STEP_2;
                    mTimeUpdate = 0;
                    otherKoopa->mTimeUpdate = 0;
                    m_physics.setBaseVelocityX(0);
                    otherKoopa->getComponent<Physics2D>().setBaseVelocityX(0);
                }
            }
            else if (otherKoopa->getState() == STEP_3) {
                // Bị shell đang di chuyển va chạm vào
                hit(true);
                this->toObject()->destroy();
            }
            else {
                // Va chạm bình thường giữa 2 koopa, đổi hướng
                if (side == Direction::LEFT || side == Direction::RIGHT) {
                    m_dir *= -1;
                }
            }
        }
        else {
            // Xử lý va chạm với các enemy khác
            if (mState == STEP_3) {
                // Shell đang di chuyển sẽ tiêu diệt enemy khác
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


void EnemiesKoopaTroopa::hit(bool isDestroy) {
    if (isDestroy) {
        mState = STEP_2;
        m_anim.loadFromJsonFile("Resources/Animations/koopaShell.json");
        m_anim.play(0);
    }
}

void EnemiesKoopaTroopa::update() {
    if (m_isDead) {
        return;
    }

    if (mState == NORMAL) {
        if (mLive >= 2) {
            m_physics.setBaseVelocityY(m_speedY * m_dirY);
            //m_physics.setAcceleration(Vector2f(0, 0.001 * m_dir));
        }
        else {
            m_physics.setBaseVelocityY(0);
        }
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
            m_anim.play(1);
        }
        if (mTimeUpdate >= 300) {
            mState = NORMAL;
            m_transform.setSize(16, 24);
            m_anim.loadFromJsonFile("Resources/Animations/koopa.json");
            m_anim.play(0);
            mTimeUpdate = 0;
        }
    }
    else if (mState == STEP_3) {
        // Mai rùa di chuyển nhanh
        m_physics.setBaseVelocityX(m_speed * m_dir * 2);
    }

    if (mIsStep2) {
        m_transform.setSize(16, 16);
        m_anim.loadFromJsonFile("Resources/Animations/koopaShell.json");
        m_anim.play(0);
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


EnemiesKoopaTroopa::State EnemiesKoopaTroopa::getState() {
    return mState;
}