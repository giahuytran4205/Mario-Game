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
        return; // Không xử lý va chạm nếu Goomba đã chết
    }
	if (col.m_entity->isDerivedFrom<Projectile>()) {
		destroy();
	}

    if (col.m_entity->isType<Mario>()) {
        // get mario
        auto gameScenen = dynamic_cast<GameScene*>(this->getParent());

        if (gameScenen != nullptr) {
            auto& mario = gameScenen->getMario();
            auto stateMario = mario.getAbility();
            switch (stateMario)
            {
            case Mario::Ability::REGULAR:  /////////////////từ khúc này trở đi là a ứng biến theo logic thôi chứ không rõ cách 
            {
                if (side == Direction::UP) {
                    m_sound.play(SoundTrack::STOMP);
                    hit(true);
                    col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
                }
                else {
                    col.m_entity->convertTo<Mario>()->dead();
                }
                break;
            }
            case Mario::Ability::SUPER:
            {
                if (side == Direction::UP) {
                    m_sound.play(SoundTrack::STOMP);
                    hit(true);
                    col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
                }
                else {
                    // TODO
                    mario.setAbility(Mario::Ability::REGULAR);
                }
                break;
            }
            case Mario::Ability::FIERY:
            {
                break;
            }
            case Mario::Ability::INVINCIBLE:
            {
                break;
            }


            default:
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
                m_speed = -m_speed; // Đổi hướng khi va chạm
            }
        }
    

    // TODO: merge ...
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
}
