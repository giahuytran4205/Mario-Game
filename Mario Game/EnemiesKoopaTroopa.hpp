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

class EnemiesKoopaTroopa : public Enemy
{
private:
    enum State {
        WALK,
        SHELL,
        SHELL_FLASHING,
        DIE
    };
    AutoControl& m_autoControl;
    SoundComponent& m_sound;
    bool m_isDead;
    bool m_isInShell;
    bool m_isShellMoving;
    float m_speed_Vy = 0.0f;
    const float G = 0.001f;
    float m_speed = 0.05f;
    int m_movingDirection; // Hướng di chuyển
    int m_flashTimer; // Bộ đếm thời gian chớp khi trong mai
    State m_currentState; // Lưu trữ trạng thái hiện tại
    friend class EnemiesGoomba; // goomba có tương tác với trạng thái shell của koopa

public:

    EnemiesKoopaTroopa(Object* parent = nullptr);
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void hit(bool isDestroy);
    void update();
    State getState() const; // Thêm hàm getState
};

