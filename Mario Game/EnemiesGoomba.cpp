#include "EnemiesGoomba.h"
#include "EnemiesBuzzyBeetle.h"
#include "EnemiesKoopaTroopa.h"

EnemiesGoomba::EnemiesGoomba(Object* parent)
{
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
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
    m_transform.move(m_speed, 0);
}
