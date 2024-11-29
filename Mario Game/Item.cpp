// Item.cpp - Implementation file
#include "Item.hpp"
#include "GameManager.hpp"
#include "Mario.hpp"

Item::Item(Object* parent) : Item(ItemType::Coin, parent) {
}

Item::Item(ItemType type, Object* parent) :
    m_type(type),
    m_isPlayAnim(true),
    m_active(true) {

    m_parent = parent;
    m_elapsedTime = 0;
    m_index = 0;

    m_collision = &addComponent<Collision>();
    auto& physics = addComponent<Physics2D>();

    m_transform.getRect().width = 16;
    m_transform.getRect().height = 16;
    m_transform.getRect().setAnchor({ 0.5f, 0.5f });

    physics.setGravity(0.00625f / 8);

    if (type != ItemType::FireFlower) {
        physics.setBaseVelocityY(-0.15f);
    }

    switch (type) {
    case ItemType::OneUpMushroom:
        m_debugColor = Color::Green;
        break;
    case ItemType::MagicMushroom:
        m_debugColor = Color::Red;
        break;
    case ItemType::FireFlower:
        m_debugColor = Color(255, 69, 0);
        physics.setEnableGravity(false);
        break;
    case ItemType::Starman:
        m_debugColor = Color::Yellow;
        break;
    case ItemType::KoopaShell:
        m_debugColor = Color(0, 255, 255);
        break;
    case ItemType::BuzyShell:
        m_debugColor = Color(128, 0, 128);
        break;
    case ItemType::Coin:
        m_debugColor = Color::Yellow;
        break;
    default:
        m_debugColor = Color::White;
    }

    m_renderOrder = 4;
}

Item::Item(float x, float y, float width, float height, ItemType type) : Item(type, nullptr) {
    m_transform.getRect().setSize(Vector2f(width, height));
    m_transform.setPosition(x, y);
}


Item::~Item() {
}
void Item::update() {
    if (!m_active) return;

    auto& physics = getComponent<Physics2D>();

    // Start horizontal movement only after item has popped up
    if ((m_type == ItemType::OneUpMushroom || m_type == ItemType::MagicMushroom) &&
        physics.getBaseVelocity().x == 0 && physics.getVelocity().y >= 0) {
        physics.setBaseVelocity({ 0.05f, physics.getBaseVelocity().y }); // Start moving right
    }

    // Handle animation if enabled
    if (m_isPlayAnim && !m_anim.empty()) {
        if (m_elapsedTime <= 0) {
            m_elapsedTime = m_anim[m_index].duration;
            m_sprite.setTexture(m_anim[m_index].texture);
            m_index++;
            m_index %= m_anim.size();
        }
        else {
            m_elapsedTime -= deltaTime.asMilliseconds();
        }
    }

    // Type-specific behavior updates
    switch (m_type) {
    case ItemType::Starman:
        // Bounce behavior for star
        if (physics.getVelocity().y == 0) {
            physics.setBaseVelocity({ physics.getBaseVelocity().x, -0.1f });
        }
        break;

    case ItemType::KoopaShell:
    case ItemType::BuzyShell:
        // Shells slide when hit
        if (physics.getBaseVelocity().x != 0) {
            physics.setBaseVelocity({ physics.getBaseVelocity().x, 0 });
        }
        break;
    }

    // Check if hit wall and reverse direction for moving items
    if ((m_type == ItemType::OneUpMushroom || m_type == ItemType::MagicMushroom) &&
        physics.getBaseVelocity().x != 0) {
        if (getComponent<Transform2D>().getPosition().x == getComponent<Transform2D>().getLastPosition().x) {
            auto vel = physics.getBaseVelocity();
            physics.setBaseVelocity({ -vel.x, vel.y });
        }
    }
}

void Item::render() {
    // Draw debug colored rectangle
    RectangleShape shape({ 16, 16 });
    shape.setFillColor(m_debugColor);
    shape.setPosition(getComponent<Transform2D>().getPosition());
    GameManager::getInstance()->getRenderWindow().draw(shape);
}

void Item::onCollisionEnter(Collision& col) {
    // Handle collisions with Mario
    if (col.m_entity->isType<Mario>()) {
        switch (m_type) {
        case ItemType::KoopaShell:
        case ItemType::BuzyShell: {
            // Shells chỉ thay đổi vận tốc khi va chạm, không bị destroy
            auto& physics = getComponent<Physics2D>();
            float direction = col.m_entity->getComponent<Transform2D>().getPosition().x >
                getComponent<Transform2D>().getPosition().x ? -1.0f : 1.0f;

            // Nếu shell đang di chuyển, dừng lại
            if (physics.getBaseVelocity().x != 0) {
                physics.setBaseVelocity({ 0, 0 });
            }
            // Nếu shell đứng yên, cho nó di chuyển
            else {
                physics.setBaseVelocity({ 0.2f * direction, 0 });
            }
            break;
        }

        default:
            // Các item khác bị collect và destroy
            m_active = false;
            destroy();
            break;
        }
    }
    // Bounce off walls for moving items
    else if (col.m_entity->isType<Block>()) {
        if ((m_type == ItemType::OneUpMushroom || m_type == ItemType::MagicMushroom) ||
            // Thêm xử lý va chạm với tường cho shells khi đang di chuyển
            ((m_type == ItemType::KoopaShell || m_type == ItemType::BuzyShell) &&
                getComponent<Physics2D>().getBaseVelocity().x != 0)) {
            auto& physics = getComponent<Physics2D>();
            physics.setBaseVelocity({ -physics.getBaseVelocity().x, physics.getBaseVelocity().y });
        }
    }
}


void Item::setAnim(vector<Frame>& anim) {
    m_anim = anim;
    if (!m_anim.empty()) {
        m_sprite.setTexture(m_anim[0].texture);
    }
}

void Item::setPosition(const Vector2f& pos) {
    Vector2f adjustedPos = pos;
    adjustedPos.y -= m_transform.getRect().height / 2;

    m_transform.setPosition(adjustedPos);
}