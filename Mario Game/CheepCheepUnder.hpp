#pragma once
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"
#include "Mario.hpp"

class CheepCheepUnder : public Enemy {
private:
    Mario& m_mario;
    bool m_isDead; // Trạng thái chết
    bool m_isJumping; // Trạng thái nhảy
    float m_jumpSpeedX; // Tốc độ ngang
    float m_jumpSpeedY; // Tốc độ dọc
    float m_gravity; // Lực trọng lực
    float m_timer; // Bộ đếm thời gian
    float m_startX; // Vị trí bắt đầu trên trục X
    float m_startY; // Vị trí bắt đầu trên trục Y
    bool mIsFall{ false };

    float mDistanceActiveX{ -1 };

public:
    CheepCheepUnder(Mario& mario, Object* parent = nullptr);
    void update() override;
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void startJump(); // Bắt đầu nhảy
    void hit(); // Xử lý trạng thái chết
};