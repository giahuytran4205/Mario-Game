#include "EnemiesGoomba.hpp"
#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesKoopaTroopa.hpp"

EnemiesGoomba::EnemiesGoomba(Object* parent) : m_autoControl(addComponent<AutoControl>())
{
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Goomba.json");
	m_anim.play(State::WALK);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);
}

void EnemiesGoomba::onCollisionEnter(Collision& col, const Direction& side)
{
	if (col.m_entity->isDerivedFrom<Projectile>()) {
		destroy();
	}

    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            hit(true);
			col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
        }
     
    }
    else if (col.m_entity->isDerivedFrom<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
			m_dir *= -1;
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
		m_anim.play(State::DIE);
		getComponent<Physics2D>().setEnable(false);
		getComponent<Collision>().setEnable(false);
		m_autoControl.addWaitForMiliseconds(1000);
		m_autoControl.addAction([&]() { destroy(); });
    }
    // todo enmation
}

void EnemiesGoomba::update()
{
	m_physics.setBaseVelocityX(m_speed * m_dir);
}
