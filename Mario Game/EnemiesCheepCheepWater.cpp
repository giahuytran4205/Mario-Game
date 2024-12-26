//#include "EnemiesCheepCheepWater.h"
//
//EnemiesCheepCheepWater::EnemiesCheepCheepWater(Mario& mario, Object* parent):
//	EnemiesCheepCheepBase(mario, parent)
//{
//}
//
//void EnemiesCheepCheepWater::update()
//{
//    auto Post = m_transform.getWorldPosition();
//    auto LastPos = m_transform.getLastPosition();
//    const auto posMario = mMario.getPos();
//
//    auto const Distance = std::abs(Post.x - posMario.x);
//    if (Distance < 200 && mIsDone == false) {
//        mIsActive = true;
//    }
//
//    if (mIsActive) {
//        double moveX = -0.1, moveY = 0.1;
//        if ((LastPos.y - posMario.y) * moveY > 0) {
//            moveY = -moveY;
//        }
//        Vector2f move(moveX, moveY);
//        m_transform.move(move);
//    }
//
//    if (Distance > 1000 && mIsActive == true) {
//        mIsActive = false;
//        mIsDone = true;
//        dead();
//    }
//
//}
