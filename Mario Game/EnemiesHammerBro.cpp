#include "EnemiesHammerBro.hpp"

// TODO add 2 platform
EnemiesHammerBro::EnemiesHammerBro(Mario& mario, const Vector2f pos, Object* parent):
	Enemy(parent, false),
	mMario(mario)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/hammer-bros.json");
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0, 0);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0, 0);

	mMinActiveX = std::max(0.0f, pos.x - RANGE_ACTIVE);
	mMaxActiveX = pos.x + RANGE_ACTIVE;

    m_physics.setElastic(false);
    m_physics.setEnableGravity(false);

	for (int i = 0; i < 20; i++) {
		EnemiesHammer* tmp	= new EnemiesHammer(parent);
		mHammer.push_back(tmp);
	} 
}
 
void EnemiesHammerBro::onCollisionEnter(Collision& col, const Direction& side)
{
}

void EnemiesHammerBro::hit(bool isDestroy)
{
}

//TODO 2 platform
void EnemiesHammerBro::update()
{
    auto Post = m_transform.getWorldPosition();
    auto LastPos = m_transform.getLastPosition();
    const auto posMario = mMario.getPos();

    mCnt++;

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

        int random = std::rand() % 40 + 40 ;
		
        Vector2f dest = { posMario.x + random, Post.y };
        const auto Distance = std::abs(Post.x - dest.x);
        const auto t = Distance *10;
        m_autoControl.addMoveByPoint(dest, t, { 0, 0 }, [&](int time) {});

        // find
        if (mCnt > 100) {
            mCnt = 0;
            auto it = std::find_if(mHammer.begin(), mHammer.end(), [&](auto& hammer) {
                return hammer->isActive() == false;
                });
            if (it != mHammer.end()) {
                const bool isRight = false;
                (*it)->getComponent<Transform2D>().setWorldPosition(Post.x + ((isRight ? 1 : -1) * (*it)->getTransform2D().getSize().x),
                    Post.y - (*it)->getTransform2D().getSize().y);
                (*it)->setActive(Post, posMario);
            }
        }

    }
}

