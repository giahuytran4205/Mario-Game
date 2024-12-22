#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
class EnemiesPiranhaPlant: public Item
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
    int mTimeCnt{ 0 };
    const int TIME_SHOW{ 250 };
    const int TIME_HIDE{ 250 };
    const int TIME_SHOWING{ 250 };
    const int TIME_HIDEING{ 250 };
    Mario& mMario;
    bool mIsMarioOnTop{ false };
    public:
    EnemiesPiranhaPlant(Mario& mario, Object* parent = nullptr);
    ~EnemiesPiranhaPlant() = default;
	void onCollisionEnter(Collision& col, const Direction& side) override;
	void update();
	State getState();
    void setHide(bool isHide);

};

