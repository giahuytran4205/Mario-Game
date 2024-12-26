//#include "CheepCheepUnder.hpp"
//#include "gamemanager.hpp"
//
//CheepCheepUnder::CheepCheepUnder(Mario* mario, Object* parent)
//    : Enemy(parent),
//    m_mario(mario),
//    m_isDead(false),
//    m_isJumping(false),
//    m_jumpSpeedX(15.0f),  // Tốc độ ngang
//    m_jumpSpeedY(-10.0f), // Tốc độ dọc ban đầu
//    m_gravity(0.15f),     // Lực trọng lực
//    m_timer(0.0f),       // Bộ đếm thời gian
//    m_startX(0.0f),
//    m_startY(1000)       // Vị trí dưới màn hình
//{
//    m_transform.setSize(16, 16);
//    m_anim.loadFromJsonFile("Resources/Animations/CheepCheep.json");
//    m_anim.play(0); // Hoạt ảnh di chuyển
//
//    m_sprite.setParent(this);
//    m_sprite.getComponent<Transform2D>().setAnchor(0.5f, 0.5f);
//    m_sprite.setRenderOrder(3);
//    m_transform.setAnchor(0.5f, 0.5f);
//
//    // Lật hình ảnh nếu cần
//    m_sprite.setScale(-1, 1); // Lật trục Y
//
//    // Tắt trọng lực và bật chế độ xuyên vật thể
//    m_physics.setEnableGravity(false);
//    m_physics.setStatic(true);
//    getComponent<Collision>().setTrigger(true); // Cho phép đi xuyên vật thể
//
//    // Đặt vị trí ban đầu
//    m_transform.setPosition(m_startX, m_startY);
//}
//
//void CheepCheepUnder::update() {
//    if (m_isDead) {
//        return; // Không cập nhật nếu đã chết
//    }
//
//    // Cập nhật bộ đếm thời gian
//    m_timer += GameManager::getInstance()->getDeltaTime().asSeconds();
//
//    // Mỗi 10 giây, thực hiện một lần nhảy
//    if (m_timer >= 10.0f) {
//        startJump();
//        m_timer = 0.0f; // Reset bộ đếm
//    }
//
//    // Nếu đang nhảy, cập nhật vị trí theo parabol
//    if (m_isJumping) {
//        m_transform.move(Vector2f(m_jumpSpeedX, m_jumpSpeedY)); // Di chuyển
//        m_jumpSpeedY += m_gravity; // Áp dụng trọng lực
//
//        // Nếu đối tượng rơi quá xa màn hình (để tránh lỗi logic)
//        if (m_transform.getWorldPosition().y > 2000) {
//            m_transform.setPosition(m_startX, m_startY); // Quay về vị trí ban đầu
//            m_isJumping = false;
//        }
//    }
//}
//void CheepCheepUnder::startJump() {
//    m_isJumping = true;
//    m_jumpSpeedY = -5.0f; // Tốc độ dọc ban đầu
//    m_jumpSpeedX = 5.5f; // Tốc độ ngang
//}
//
//void CheepCheepUnder::onCollisionEnter(Collision& col, const Direction& side) {
//    if (m_isDead) {
//        return; // Không xử lý va chạm nếu đã chết
//    }
//
//    if (col.m_entity->isType<Mario>()) {
//        if (side == Direction::UP) {
//            m_sound.play(SoundTrack::STOMP);
//            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
//            hit(); // CheepCheepUnder chết
//        }
//        else {
//            col.m_entity->convertTo<Mario>()->dead(); // Mario chết
//        }
//    }
//}
//
//void CheepCheepUnder::hit() {
//    if (m_isDead) return; // Đảm bảo chỉ xử lý khi chưa chết
//
//    m_isDead = true;
//    m_anim.play(1); // Hoạt ảnh chết
//    m_sprite.setScale(1, -1); // Lật hình ảnh khi chết
//    getComponent<Collision>().setTrigger(true); // Tắt hitbox
//    getComponent<Physics2D>().setStatic(true);  // Dừng mọi lực vật lý
//
//    // Xóa đối tượng sau 1 giây
//    m_autoControl.addWaitForMiliseconds(1000);
//    m_autoControl.addAction([this]() { destroy(); });
//}