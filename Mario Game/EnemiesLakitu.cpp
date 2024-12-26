#include "EnemiesLakitu.h"
#include "GameManager.hpp"



EnemiesLakitu::EnemiesLakitu(Mario& mario, const Vector2f pos, Object* parent) :
    Enemy(parent),
    mMario(mario),
    m_isDead(false)
{
    m_transform.setSize(16, 24);
    m_anim.loadFromJsonFile("Resources/Animations/Lakiku.json");
    m_anim.play(0);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0, 0);

	mMinActiveX = std::max(0.0f, pos.x - RANGE_ACTIVE);
	mMaxActiveX = pos.x + RANGE_ACTIVE;

	m_physics.setElastic(false);
    m_physics.setEnableGravity(false);


}


void EnemiesLakitu::onCollisionEnter(Collision& col, const Direction& side) {
    if (m_isDead) {
        return; // Không xử lý nếu Lakitu đã chết
    }

    // Kiểm tra va chạm với Mario
    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
            // Phát âm thanh khi bị tiêu diệt
            m_sound.play(SoundTrack::STOMP);

            // Làm Mario nảy lên một chút
            col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.2f);

            // Tiêu diệt Lakitu
            hit(true);
            this->toObject()->destroy();
        }
        else {
            // Mario chết nếu va chạm từ các phía khác
            col.m_entity->convertTo<Mario>()->dead();
        }
    }
}

void EnemiesLakitu::hit(bool isDestroy) {
    if (isDestroy) {
        m_isDead = true;

        // Chạy hoạt ảnh chết nếu cần (ví dụ, hoạt ảnh số 1)
        m_anim.play(1);

        // Vô hiệu hóa va chạm và dừng mọi di chuyển
        getComponent<Collision>().setTrigger(true);
        m_physics.setBaseVelocityX(0.0f);
        m_physics.setBaseVelocityY(0.0f);

        // Xóa đối tượng sau 1 giây
        m_autoControl.addWaitForMiliseconds(1000);
        m_autoControl.addAction([this]() { destroy(); });
    }
}


void EnemiesLakitu::update()
{
    if (m_isDead) {
        return; // Không cập nhật nếu đã chết
    }

    auto Post = m_transform.getWorldPosition();
    auto LastPos = m_transform.getLastPosition();
    const auto posMario = mMario.getPos();

    auto it = std::find_if(mSpinys.begin(), mSpinys.end(), [&](auto spiny) {
        return spiny->isActive() == false;
        });
    if (it != mSpinys.end()) {
		mSpinys.erase(it);
    }
	

    if (posMario.x > mMinActiveX && posMario.x < mMaxActiveX) {
        if (mIsActive == false) {
        }
		mIsActive = true;
    }
    else
    {
		mIsActive = false;

    }


    if (mIsActive) {
		if (m_autoControl.isControlled())
			return;


            auto  Distance = std::abs(Post.x - posMario.x);
            if (static_cast<int>(Distance) == 0) {
				Distance = 20;
            }
            int random = std::rand() % 80;
            
            float newPosX;

            if (Post.x > posMario.x) {
                //random = -random;
                newPosX = -Distance - random;
            }
            else {
                newPosX = Distance + random;
            }
			Vector2f dest = { Post.x  + newPosX, Post.y };
            m_autoControl.addMoveByPoint(dest, 3000, { 0, 0 }, [&](int time) {  });
            
            // find
            if (mSpinys.size() < MAX_SPINY) {
				//auto spiny = std::make_shared<EnemiesSpiny>(this->getParent());
                auto spiny = new EnemiesSpiny(this->getParent());
                const bool isRight = (Post.x < posMario.x);
                spiny->getComponent<Transform2D>().setWorldPosition(Post.x + ((isRight ? 1 : -1) * spiny->getTransform2D().getSize().x),
                    Post.y - spiny->getTransform2D().getSize().y);
                spiny->setActive(Post, posMario, isRight);
                mSpinys.push_back(spiny);

            }
          

        //const auto posGame = GameManager::getInstance()->getView().getCenter();
        //const auto sizeView = GameManager::getInstance()->getView().getSize();

        //const auto left = posGame.x - sizeView.x / 2;
        //const auto right = posGame.x + sizeView.x / 2;
		


    }
}
