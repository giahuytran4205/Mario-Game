#include "EnemiesGoomba.hpp"
#include "EnemiesBuzzyBeetle.hpp"
#include "EnemiesKoopaTroopa.hpp"

EnemiesGoomba::EnemiesGoomba(Object* parent)
{
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Goomba.json");
	m_anim.play(0);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);
}

void EnemiesGoomba::onCollisionEnter(Collision& col, const Direction& side)
{
    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            hit(true); 
        }
     
    }
    else if (col.m_entity->isType<Block>()) {
            if (side == Direction::LEFT || side == Direction::RIGHT) {
                m_onWall = true;
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
		m_anim.play(1);
		destroy();
    }
    // todo enmation
}

void EnemiesGoomba::update()
{
    if (m_onWall) {
        m_speed = -m_speed;
        m_onWall = false;
    }
    auto lastPost = m_transform.getLastPosition();
    if (lastPost.y < 430) {
        m_speed_Vy += G * (float)deltaTime.asMilliseconds();
    }
    else
    {
        m_speed_Vy = 0;
    }
    m_transform.move(m_speed, m_speed_Vy);
}
