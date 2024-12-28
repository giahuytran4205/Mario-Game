#include "EnemiesGoomba.hpp"
#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesKoopaTroopa.hpp"
#include "GameScene.hpp"

EnemiesGoomba::EnemiesGoomba(Object* parent): Enemy(parent, true){
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Goomba.json");
	m_anim.play(State::WALK);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);
    m_isDead = false; // Khởi tạo trạng thái sống của Goomba
}
void EnemiesGoomba::onCollisionEnter(Collision& col, const Direction& side)
{
    if (m_isDead) {
        getComponent<Collision>().setTrigger(true); // Tắt collision khi đã chết
        return;
    }

    if (col.m_entity->isDerivedFrom<Projectile>()) {
        destroy();
        return;
    }

    if (col.m_entity->isType<Mario>()) {
        auto gameScene = dynamic_cast<GameScene*>(this->getParent());
        if (gameScene == nullptr) return;

        auto& mario = gameScene->getMario();
        auto stateMario = mario.getAbility();

        // Xử lý va chạm từ trên xuống
        if (side == Direction::UP) {
            m_sound.play(SoundTrack::STOMP);
            hit(true);
            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
            return;
        }

        // Xử lý va chạm từ các hướng khác theo trạng thái Mario
        switch (stateMario) {
        case Mario::Ability::REGULAR:
        {
            col.m_entity->convertTo<Mario>()->dead();
            break;
        }
        case Mario::Ability::SUPER:
        case Mario::Ability::FIERY:
        {
            // Chuyển về dạng nhỏ và bắt đầu đếm thời gian bất tử
            mario.setAbility(Mario::Ability::REGULAR);
            m_invincibleTimer = 2.0f; // 2 giây bất tử
            break;
        }
        case Mario::Ability::INVINCIBLE:
        {
            // Goomba biến mất khi Mario đang ở trạng thái bất tử
            hit(true);
            break;
        }
        }
    }
    else if (col.m_entity->isDerivedFrom<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            m_dir *= -1;
        }
    }
    else if (col.m_entity->isDerivedFrom<Enemy>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            m_speed = -m_speed;
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
        if (tropa->getState() == EnemiesKoopaTroopa::STEP_2) {
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
    // todo enmation
}

void EnemiesGoomba::update()
{
	m_physics.setBaseVelocityX(m_speed * m_dir);
    if (m_isDead) {
        return; // Không cập nhật nếu Goomba đã chết
    }

    if (m_invincibleTimer > 0) {
        m_invincibleTimer -= 0.016f; // Giả sử 60 FPS, mỗi frame là 1/60 giây
        if (m_invincibleTimer < 0) {
            m_invincibleTimer = 0;
        }
    }
}
