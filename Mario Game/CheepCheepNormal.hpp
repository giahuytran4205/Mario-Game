#pragma once
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"
#include "Mario.hpp"
#include "Block.hpp"
#include "Physics2D.hpp"
#include "Transform2D.hpp"
#include "GameManager.hpp"

class Mario;

class EnemiesCheepCheepNormal : public Enemy {
private:
    Mario* m_mario;
    float m_speed;
    int mTimeUpdate;
    bool mIsDone;
    bool mIsActive;
    bool m_isDead; // Trạng thái chết
public:
    EnemiesCheepCheepNormal(Mario* mario = nullptr, Object* parent = nullptr); // Sửa tham số cho khớp tại ban đầu nhìn video nhầm version là lost level gì đấy là nó truy đuổi
    void update() override;
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void hit(); // Hàm xử lý trạng thái chết
};