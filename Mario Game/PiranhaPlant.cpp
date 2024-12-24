#include "PiranhaPlant.hpp"

PiranhaPlant::PiranhaPlant(Object* parent) :
    m_autoControl(addComponent<AutoControl>()),
    m_sound(addComponent<SoundComponent>()),
    m_isDead(false),
    m_isActive(false),
    m_timer(0.0f),
    m_positionOffset(0.0f),
    m_isRising(false)
{
    m_transform.setSize(16, 24); // Kích thước của Piranha Plant
    m_anim.loadFromJsonFile("Resources/Animations/pi.json");
    m_anim.play(0); // Default state (hoa chưa mở miệng)
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);

    // Đặt vật thể là static để không bị đẩy
    getComponent<Physics2D>().setStatic(true);
}

void PiranhaPlant::onCollisionEnter(Collision& col, const Direction& side)
{
    if (m_isDead) {
        return; // Không xử lý va chạm nếu Piranha Plant đã chết
    }

    if (m_isActive && col.m_entity->isType<Mario>()) {
        col.m_entity->convertTo<Mario>()->dead(); // Mario chết khi chạm vào cây đang hoạt động
    }
}

void PiranhaPlant::hit(bool isDestroy)
{
    if (isDestroy) {
        m_isDead = true;
        m_anim.stop(); // Ngừng hoạt ảnh khi bị tiêu diệt
        getComponent<Collision>().setTrigger(true);
        m_autoControl.addWaitForMiliseconds(1000);
        m_autoControl.addAction([&]() { destroy(); });
    }
}

void PiranhaPlant::update()
{
    if (m_isDead) {
        return; // Không cập nhật nếu Piranha Plant đã chết
    }

    m_timer += deltaTime.asMilliseconds();

    if (m_timer >= 3000.0f) { // Chuyển trạng thái giữa trồi lên và hạ xuống mỗi 3 giây
        m_isRising = !m_isRising;
        m_timer = 0.0f;
    }

    if (m_isRising) {
        m_positionOffset += 0.1f * deltaTime.asMilliseconds(); // Trồi lên dần
        if (m_positionOffset >= 16.0f) { // Đã trồi hết mức
            m_positionOffset = 16.0f;
            m_isActive = true;
            m_anim.play(0); // Bắt đầu hoạt ảnh cắn
        }
    }
    else {
        m_positionOffset -= 0.1f * deltaTime.asMilliseconds(); // Hạ xuống dần
        if (m_positionOffset <= 0.0f) { // Đã hạ hết mức
            m_positionOffset = 0.0f;
            m_isActive = false;
            m_anim.play(1); // Trạng thái hoa chưa mở miệng
        }
    }

    // Cập nhật vị trí dựa trên offset
    m_transform.setPosition(m_transform.getPosition().x, m_transform.getPosition().y - m_positionOffset);
}
