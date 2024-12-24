#include "EnemiesKoopaTroopa.hpp"


EnemiesKoopaTroopa::EnemiesKoopaTroopa(Object* parent) :
    m_autoControl(addComponent<AutoControl>()),
    m_sound(addComponent<SoundComponent>()),
    m_currentState(WALK) // Khởi tạo trạng thái
{
    m_transform.setSize(16, 24); // Koopa Troopa lớn hơn Goomba
    m_anim.loadFromJsonFile("Resources/Animations/koopa.json");
    m_anim.play(0); // WALK state
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);
    m_movingDirection = 1; // -1 là sang trái, 1 là sang phải
    m_isDead = false;
    m_isInShell = false;
    m_isShellMoving = false;
    m_flashTimer = 0;
}

void EnemiesKoopaTroopa::onCollisionEnter(Collision& col, const Direction& side)
{
    if (m_isDead) {
        return; // Không xử lý va chạm nếu Koopa Troopa đã chết
    }

    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            if (!m_isInShell) {
                m_isInShell = true;
                m_currentState = SHELL;
                m_anim.loadFromJsonFile("Resources/Animations/koopaShell.json");
                m_anim.play(0); // SHELL state
                getComponent<Physics2D>().setStatic(true);
                m_sound.play(SoundTrack::STOMP);
            }
            else {
                m_isShellMoving = !m_isShellMoving;
                if (m_isShellMoving) {
                    m_currentState = SHELL; // Chuyển trạng thái shell khi bắt đầu lăn
                    m_anim.play(0); // SHELL state
                    m_sound.play(SoundTrack::STOMP);
                }
                m_movingDirection *= (m_isShellMoving ? 1 : 0); // Đặt hướng nếu đang lăn
            }

            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
        }
        else {
            col.m_entity->convertTo<Mario>()->dead();
        }
    }
    else if (col.m_entity->isType<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            if (m_isShellMoving) {
                m_movingDirection *= -1; // Đảo chiều nếu va chạm trong trạng thái lăn
            }
            else {
                m_movingDirection *= -1; // Đảo chiều trong trạng thái đi bộ
            }
        }
    }
}

void EnemiesKoopaTroopa::hit(bool isDestroy)
{
    if (isDestroy) {
        m_isDead = true;
        m_currentState = DIE; // Chuyển trạng thái DIE
        m_anim.play(0); // DIE state
        getComponent<Physics2D>().setStatic(true);
        getComponent<Collision>().setTrigger(true);
        m_autoControl.addWaitForMiliseconds(1000);
        m_autoControl.addAction([&]() { destroy(); });
    }
}

void EnemiesKoopaTroopa::update()
{
    if (m_isDead) {
        return; // Không cập nhật nếu Koopa Troopa đã chết
    }

    if (!m_isInShell || m_isShellMoving) {
        m_physics.setBaseVelocityX(m_speed * m_movingDirection);
        m_sprite.setScale(m_movingDirection == -1 ? 1.f : -1.f, 1.f); // Flip sprite dựa trên hướng di chuyển
    }
    else {
        m_physics.setBaseVelocityX(0); // Dừng lại nếu đang trong mai và không lăn
    }

    if (m_isInShell && !m_isShellMoving) {
        m_flashTimer += deltaTime.asMilliseconds();
        if (m_flashTimer >= 5000) {
            m_isInShell = false;
            m_flashTimer = 0;
            m_currentState = WALK;
            m_anim.loadFromJsonFile("Resources/Animations/Koopa.json");
            m_anim.play(0); // WALK state
            getComponent<Physics2D>().setStatic(false);
        }
        else if (m_flashTimer % 500 < 250) {
            m_anim.play(1); // SHELL_FLASHING state
        }
        else {
            m_anim.play(0); // SHELL state
        }
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

EnemiesKoopaTroopa::State EnemiesKoopaTroopa::getState() const
{
    return m_currentState; // Trả về trạng thái hiện tại
}
