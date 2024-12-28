#pragma once
#include "Enemy.hpp"
#include "Mario.hpp"

class EnemiesPiranhaPlant: public Enemy
{
 public:
    enum State {
        HIDDEN,
        SHOW,
        HIDING,
        SHOWING   
    };

private:
    State mState { HIDDEN };
    //int mTimeCnt{ 0 };
    //const int TIME_SHOW{ 250 };
    //const int TIME_HIDE{ 250 };
    //const int TIME_SHOWING{ 250 };
    //const int TIME_HIDEING{ 250 };

    static const int TIME_RAISING = 1000;

    Mario& mMario;
    //bool mIsMarioOnTop{ false };

    float posYHide = -1;
    float posYTop = -1;
 public:
    EnemiesPiranhaPlant(Mario& mario, Object* parent = nullptr);
    ~EnemiesPiranhaPlant() = default;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update();
	State getState();
    void setHide(bool isHide);

};

