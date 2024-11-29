#pragma once
#include "Enemy.hpp"
#include "GameManager.hpp" // Cho deltaTime macro
#include "SFML/Graphics.hpp"

// Định nghĩa các màu tùy chỉnh
namespace CustomColors {
    const Color Brown(139, 69, 19);
    const Color Pink(255, 192, 203);
    const Color DarkGray(169, 169, 169);
}

// Goomba
class Goomba : public Enemy {
public:
    Goomba() : Enemy(EnemyType::GOOMBA, CustomColors::Brown, Vector2f(16, 16)) {
        m_speed = 0.05f;
    }
};

// KoopaParatroopa
class KoopaParatroopa : public Enemy {
private:
    float m_initialY;
    float m_amplitude;
    float m_frequency;

public:
    KoopaParatroopa() : Enemy(EnemyType::KOOPA_PARATROOPA, Color::Red, Vector2f(16, 24)) {
        m_speed = 0.04f;
        m_amplitude = 32.0f;
        m_frequency = 0.002f;
        m_physics2D.setEnableGravity(false);
    }

    void update() override {
        Enemy::update();
        float newY = m_initialY + m_amplitude * sin(m_frequency * GameManager::getDeltaTime().asMilliseconds());
        m_transform.setPosition(m_transform.getPosition().x, newY);
    }

    void init() override {
        Enemy::init();
        m_initialY = m_transform.getPosition().y;
    }
};

// BillBlaster
class BillBlaster : public Enemy {
private:
    int m_shootInterval;
    int m_currentInterval;

public:
    BillBlaster() : Enemy(EnemyType::BILL_BLASTER, CustomColors::DarkGray, Vector2f(16, 32)) {
        m_physics2D.setEnableGravity(false);
        m_shootInterval = 2000;
        m_currentInterval = 0;
    }

    void update() override {
        m_currentInterval += GameManager::getDeltaTime().asMilliseconds();
        if (m_currentInterval >= m_shootInterval) {
            shoot();
            m_currentInterval = 0;
        }
    }

    void shoot() {
        // To be handled by GameManager
    }
};

// Cheep Cheep
class CheepCheep : public Enemy {
private:
    float m_verticalSpeed;
    float m_initialY;
    float m_amplitude;
    float m_frequency;

public:
    CheepCheep() : Enemy(EnemyType::CHEEP_CHEEP, Color::Red, Vector2f(16, 16)) {
        m_speed = 0.06f;
        m_verticalSpeed = 0.08f;
        m_amplitude = 48.0f;
        m_frequency = 0.003f;
        m_physics2D.setEnableGravity(false);
    }

    void update() override {
        float newY = m_initialY + m_amplitude * sin(m_frequency * GameManager::getDeltaTime().asMilliseconds());
        m_transform.setPosition(m_transform.getPosition().x, newY);
        m_physics2D.setBaseVelocityX(-m_speed);
    }
};

// Blooper
class Blooper : public Enemy {
private:
    bool m_isCharging;
    float m_chargeSpeed;
    int m_chargeTime;
    int m_currentChargeTime;

public:
    Blooper() : Enemy(EnemyType::BLOOPER, Color::White, Vector2f(16, 24)) {
        m_speed = 0.04f;
        m_chargeSpeed = 0.12f;
        m_chargeTime = 500;
        m_currentChargeTime = 0;
        m_isCharging = false;
        m_physics2D.setEnableGravity(false);
    }

    void update() override {
        if (m_isCharging) {
            m_currentChargeTime += GameManager::getDeltaTime().asMilliseconds();
            if (m_currentChargeTime >= m_chargeTime) {
                m_isCharging = false;
                m_currentChargeTime = 0;
            }
            m_physics2D.setBaseVelocity({ -m_chargeSpeed, m_chargeSpeed });
        }
        else {
            m_physics2D.setBaseVelocity({ 0, -m_speed });
        }
    }
};

// Lakitu
class Lakitu : public Enemy {
private:
    int m_throwInterval;
    int m_currentInterval;
    float m_targetX;
    float m_followSpeed;

public:
    Lakitu() : Enemy(EnemyType::LAKITU, Color::Yellow, Vector2f(16, 24)) {
        m_speed = 0.05f;
        m_throwInterval = 2000;
        m_currentInterval = 0;
        m_followSpeed = 0.03f;
        m_physics2D.setEnableGravity(false);
    }

    void update() override {
        // Follow player movement using transform directly instead of GameManager::getPlayer()
        Transform2D& transform = m_transform;
        float currentX = transform.getPosition().x;

        // Simple AI: Move towards center of screen if no direct player access
        float screenCenterX = GameManager::getInstance()->getView().getCenter().x;
        m_targetX = screenCenterX;

        if (abs(currentX - m_targetX) > 8.0f) {
            float direction = (m_targetX > currentX) ? 1.0f : -1.0f;
            m_physics2D.setBaseVelocityX(direction * m_followSpeed);
        }
        else {
            m_physics2D.setBaseVelocityX(0);
        }

        m_currentInterval += GameManager::getDeltaTime().asMilliseconds();
        if (m_currentInterval >= m_throwInterval) {
            throwSpinyEgg();
            m_currentInterval = 0;
        }
    }

    void throwSpinyEgg() {
        // To be handled by GameManager
    }
};

// SpinyEgg
class SpinyEgg : public Enemy {
public:
    SpinyEgg() : Enemy(EnemyType::SPINY_EGG, CustomColors::Pink, Vector2f(16, 16)) {
        m_speed = 0.0f;
        m_physics2D.setGravity(0.00625f / 4);
    }
};