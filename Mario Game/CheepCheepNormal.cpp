#include "CheepCheepNormal.hpp"
#include "Mario.hpp"
#include "GameScene.hpp" // Kiểm tra chính xác tên tệp

EnemiesCheepCheepNormal::EnemiesCheepCheepNormal(Mario* mario, Object* parent)
    : Enemy(parent),
    m_mario(mario),
    m_speed(0.1f),
    mTimeUpdate(0),
    mIsDone(false),
    mIsActive(false),
    m_isDead(false) // Goomba ban đầu chưa chết
{
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/CheepCheep.json");
    m_anim.play(0);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0.5f, 0.5f);

    // Tắt physics
    m_physics.setEnableGravity(false);
    m_physics.setStatic(true);

    // Cho phép đi xuyên tường
    getComponent<Collision>().setTrigger(true);
}
void EnemiesCheepCheepNormal::onCollisionEnter(Collision& col, const Direction& side) {
    if (m_isDead) {
        return; // Không xử lý va chạm nếu đã chết
    }

    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            m_sound.play(SoundTrack::STOMP);
            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
            hit(); // Chuyển sang trạng thái chết
        }
        else {
            col.m_entity->convertTo<Mario>()->dead();
        }
    }
}

void EnemiesCheepCheepNormal::update() {
    if (mIsDone) {
        // Nếu đang chết, cho đối tượng trôi xuống
        m_transform.move(Vector2f(0, 0.5f)); // Trôi xuống dưới

        // Kiểm tra nếu đối tượng đã ra khỏi bản đồ
        auto pos = m_transform.getWorldPosition();
        if (pos.y > 1000) { // Giả sử 1000 là giới hạn dưới của bản đồ
            destroy(); // Xóa đối tượng
        }
        return; // Không thực hiện logic khác
    }

    if (m_mario) {
        // Logic truy đuổi Mario
        auto Post = m_transform.getWorldPosition();
        auto posMario = m_mario->getComponent<Transform2D>().getWorldPosition();
        auto const Distance = std::abs(Post.x - posMario.x);

        if (Distance < 100 && !mIsDone) {
            mIsActive = true;
        }

        if (mIsActive) {
            double moveX = -0.1, moveY = 0.1;
            if ((Post.y - posMario.y) * moveY > 0) {
                moveY = -moveY;
            }
            m_transform.move(Vector2f(moveX, moveY));
        }

        if (Distance > 1000 && mIsActive) {
            mIsActive = false;
            mIsDone = true;
            destroy();
        }
    }
    else {
        // Logic mặc định nếu không có Mario
        m_transform.move(Vector2f(-0.3f, 0)); // Ví dụ: chỉ di chuyển ngang
    }
}


void EnemiesCheepCheepNormal::hit() {
    m_isDead = true; // Đánh dấu là đã chết
    m_anim.loadFromJsonFile("Resources/Animations/CheepCheepDie.json"); // Tải animation chết
    m_anim.play(2); // Chạy animation ID 1
    getComponent<Collision>().setTrigger(true); // Tắt hitbox
    getComponent<Physics2D>().setStatic(true);  // Dừng mọi lực vật lý

    // Hẹn giờ xóa đối tượng sau 1 giây
    m_autoControl.addWaitForMiliseconds(1000);
    m_autoControl.addAction([&]() { destroy(); });
}