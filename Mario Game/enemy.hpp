#pragma once
#include "Character.hpp"
#include "Physics2D.hpp"
#include "Collision.hpp"

enum class EnemyType {
    BILL_BLASTER,    // Static shooter
    BLOOPER,         // Swimming enemy
    BULLET_BILL,     // Projectile
    BUZZY_BEETLE,    // Small shell enemy
    CHEEP_CHEEP,     // Flying fish
    GOOMBA,          // Basic enemy
    HAMMER_BRO,      // Throwing enemy
    KOOPA_PARATROOPA,// Flying turtle
    KOOPA_TROOPA,    // Walking turtle
    LAKITU,          // Cloud riding thrower
    LAVA_BUBBLE,     // Jumping fire
    PIRANHA_PLANT,   // Pipe plant
    SPINY,           // Spiked enemy
    SPINY_EGG        // Thrown by Lakitu
};

class Enemy : public Character {
protected:
    Physics2D& m_physics2D;
    Collision& m_collision;
    float m_speed;
    bool m_isMovingRight;
    EnemyType m_type;
    Color m_color;      // Color for debug rendering
    Vector2f m_size;    // Size of enemy hitbox

public:
    Enemy(EnemyType type, const Color& debugColor, const Vector2f& size);
    virtual ~Enemy();

    virtual void init();
    virtual void update() override;
    virtual void onCollisionEnter(Collision& col) override;
    virtual void reverseDirection();
    virtual bool canBeStomped() const;
    virtual bool hasShell() const;
    virtual bool canFly() const;
    virtual bool canShoot() const;
};