#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"
class EnemiesGoomba : public Enemy
{
private:
    enum State {
        WALK,
        DIE
    };

    AutoControl& m_autoControl;
    bool m_isDead;
    float m_speed_Vy = 0.0f;
    const float G = 0.001f;
    float m_speed = 0.05f;
    int m_movingDirection;  // Thêm biến để theo dõi hướng di chuyển
    SoundComponent& m_sound; // Thêm soundComponent vào vì khi mario trong game gốc nhảy giết được 1 con thì sẽ có tiếng stomp nổi lên

public:
    EnemiesGoomba(Object* parent = nullptr);
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void hit(bool isDestroy);
    void update();
};