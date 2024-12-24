#include "EnemiesGoomba.hpp"
#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesKoopaTroopa.hpp"

EnemiesGoomba::EnemiesGoomba(Object* parent) :
    m_autoControl(addComponent<AutoControl>()), m_sound(addComponent<SoundComponent>()){
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Goomba.json");
    m_anim.play(State::WALK);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);
    m_movingDirection = 1; // -1 là sang trái, 1 là sang phải
    m_isDead = false; // Khởi tạo trạng thái sống của Goomba
}

void EnemiesGoomba::onCollisionEnter(Collision& col, const Direction& side)
{
    if (m_isDead) {
        return; // Không xử lý va chạm nếu Goomba đã chết
    }

    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            m_sound.play(SoundTrack::STOMP);
            hit(true);
            
            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
        }
        else {
            col.m_entity->convertTo<Mario>()->dead();
        }
    }
    else if (col.m_entity->isType<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            m_movingDirection *= -1; // Đảo chiều khi chạm tường
        }
    }
    else if (col.m_entity->isType<EnemiesBuzzyBeetle>()) {
        EnemiesBuzzyBeetle* buzzy = col.m_entity->convertTo<EnemiesBuzzyBeetle>();
        if (buzzy->getState() == EnemiesBuzzyBeetle::STEP_2) {
            hit(true);
        }
    }
    else if (col.m_entity->isType<EnemiesKoopaTroopa>()) {
        EnemiesKoopaTroopa* tropa = col.m_entity->convertTo<EnemiesKoopaTroopa>();
        if (tropa->getState() == EnemiesKoopaTroopa::SHELL) {
            hit(true);
        }
    }
}

void EnemiesGoomba::hit(bool isDestroy)
{
    if (isDestroy) {
        m_isDead = true;
        m_anim.play(State::DIE);
        getComponent<Physics2D>().setStatic(true);
        getComponent<Collision>().setTrigger(true);
        m_autoControl.addWaitForMiliseconds(1000);
        m_autoControl.addAction([&]() { destroy(); });
    }
}

void EnemiesGoomba::update()
{
    // Liên tục set vận tốc theo hướng di chuyển hiện tại
    m_physics.setBaseVelocityX(m_speed * m_movingDirection);
    if (m_isDead) {
        return; // Không cập nhật nếu Goomba đã chết
    }

    // Xử lý trọng lực
    auto lastPost = m_transform.getLastPosition();
    if (lastPost.y < 430) {
        m_speed_Vy += G * deltaTime.asMilliseconds();
        m_physics.setBaseVelocityY(m_speed_Vy);
    }
    else {
        m_speed_Vy = 0;
        m_physics.setBaseVelocityY(0);
    }
}