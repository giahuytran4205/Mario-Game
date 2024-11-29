#include "Enemy.hpp"
#include "Block.hpp"
#include "GameManager.hpp"

Enemy::Enemy(EnemyType type, const Color& debugColor, const Vector2f& size) :
    m_physics2D(addComponent<Physics2D>()),
    m_collision(addComponent<Collision>()),
    m_type(type),
    m_color(debugColor),
    m_size(size)
{
    init();
}

Enemy::~Enemy() {}

void Enemy::init() {
    // Basic physics setup
    m_speed = 0.1f;
    m_isMovingRight = true;
    m_physics2D.setGravity(0.00625f / 8);

    // Set collision box size
    m_transform.getRect().width = m_size.x;
    m_transform.getRect().height = m_size.y;

    // Create colored rectangle for debug visualization
    RectangleShape* shape = new RectangleShape();
    shape->setSize(m_size);
    shape->setFillColor(m_color);

    Texture* texture = new Texture();
    texture->create(m_size.x, m_size.y);
    Image img;
    img.create(m_size.x, m_size.y, m_color);
    texture->loadFromImage(img);
    m_sprite.setTexture(*texture);

    // Set initial velocity for moving enemies
    if (canFly()) {
        m_physics2D.setEnableGravity(false);
    }
    if (m_type != EnemyType::PIRANHA_PLANT &&
        m_type != EnemyType::BILL_BLASTER) {
        m_physics2D.setBaseVelocityX(m_speed);
    }
}

void Enemy::update() {
    if (m_type != EnemyType::PIRANHA_PLANT &&
        m_type != EnemyType::BILL_BLASTER) {
        // Basic movement for walking enemies
        if (m_isMovingRight) {
            m_physics2D.setBaseVelocityX(m_speed);
        }
        else {
            m_physics2D.setBaseVelocityX(-m_speed);
        }
    }
}

void Enemy::onCollisionEnter(Collision& col) {
    if (col.m_entity->isType<Block>()) {
        int side = m_transform.getRect().tangentSide(col.getCollider());

        if (side == 1) { // Top collision
            m_physics2D.setBaseVelocityY(m_speed / 10);
        }
        else if (side == 3) { // Bottom collision
            m_physics2D.setBaseVelocityY(0);
            m_physics2D.setVelocityY(0);
        }

        if ((side == 0 || side == 2) && !canFly()) { // Left or Right collision for ground enemies
            reverseDirection();
        }
    }
}

void Enemy::reverseDirection() {
    m_isMovingRight = !m_isMovingRight;
}

bool Enemy::canBeStomped() const {
    return m_type != EnemyType::SPINY &&
        m_type != EnemyType::PIRANHA_PLANT &&
        m_type != EnemyType::BULLET_BILL;
}

bool Enemy::hasShell() const {
    return m_type == EnemyType::KOOPA_TROOPA ||
        m_type == EnemyType::KOOPA_PARATROOPA ||
        m_type == EnemyType::BUZZY_BEETLE;
}

bool Enemy::canFly() const {
    return m_type == EnemyType::KOOPA_PARATROOPA ||
        m_type == EnemyType::CHEEP_CHEEP ||
        m_type == EnemyType::LAKITU ||
        m_type == EnemyType::BLOOPER;
}

bool Enemy::canShoot() const {
    return m_type == EnemyType::HAMMER_BRO ||
        m_type == EnemyType::BILL_BLASTER ||
        m_type == EnemyType::LAKITU;
}