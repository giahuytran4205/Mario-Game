#include "EnemiesCheepCheepNormal.h"
#include <cmath>

EnemiesCheepCheepNormal::EnemiesCheepCheepNormal(Mario& mario, Object* parent):
	EnemiesCheepCheepBase(mario, parent)
{

}

void EnemiesCheepCheepNormal::update()
{

    auto Post = m_transform.getPosition();
    auto LastPos = m_transform.getLastPosition();
    const auto posMario = mMario.getPos();

    auto const Distance = std::abs(Post.x - posMario.x);
    if (Distance < 100 && mIsDone == false) {
        mIsActive = true;
        mInitY = Post.y;
        //m_transform.setPosition(lastPost.x, 0);
        /*std::cout << "active \r\n";*/
    }
    if (mIsActive) {
       
        const auto x = mIsDead ? 0 : Velocity* mTime* std::cos(Angle * 3.14159 / 180.0);
        const auto y = Velocity * mTime * std::sin(Angle * 3.14159 / 180.0) - 0.5 * 9.8 * mTime * mTime;

        Vector2f move;
        if ((m_transform.getPosition().y > 250) && !mIsDown) {
             move = Vector2f(x, -y);
            
        }
        else {
            mIsDown = true;
            move = Vector2f(x, +y);
        }

        m_transform.move(move);

        if (m_transform.getLastPosition() .y> mInitY) {
            mIsDone = true;
            mIsActive = false;
            destroy();
        }
        //std::cout << "lastPost.y " << LastPos.y << "\r\n";

    }
    mTimeUpdate++;
}

void EnemiesCheepCheepNormal::onCollisionEnter(Collision& col, const Direction& side)
{
    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            mIsDown = true;
            mIsDead = true;
        }
    }
}
