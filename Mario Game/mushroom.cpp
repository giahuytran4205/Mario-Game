#include "Mushroom.hpp"

Mushroom::Mushroom(MushroomType type, Object* parent) :
    Item(parent),
    m_type(type),
    m_sound(addComponent<SoundComponent>())
{
    m_transform.setSize(16, 16);

    // Set texture based on type
    if (type == MushroomType::ORANGE) {
        m_anim.loadFromJsonFile("Resources/Animations/coin.json");
    }
    else {
        //m_anim.loadFromJsonFile("Resources/Animations/ORANGE-MUSHROOM.json");
    }


    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);
}

Mushroom::~Mushroom() {}

void Mushroom::onCollisionEnter(Collision& col, const Direction& side) {
    if (col.m_entity->isType<Mario>()) {
        // Play powerup sound
        m_sound.setSoundBuf(SoundBufferManager::getInstance()->getSoundBuf(SoundTrack::ONE_UP));
        m_sound.play();
        destroy();
    }
    else if (col.m_entity->isType<Block>()) {
        if (side == Direction::LEFT || side == Direction::RIGHT) {
            m_onWall = true;
        }
    }
}

void Mushroom::update() {
    if (m_onWall) {
        m_speed = -m_speed;  // Đổi hướng khi chạm tường
        m_onWall = false;
    }
    m_transform.move(m_speed, 0);  // Di chuyển trái phải
}