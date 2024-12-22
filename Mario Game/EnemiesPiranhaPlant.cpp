#include "EnemiesPiranhaPlant.h"

EnemiesPiranhaPlant::EnemiesPiranhaPlant(Mario& mario, Object* parent): Item(parent), mMario(mario)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
	m_sprite.setParent(this);
	m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
	m_sprite.setRenderOrder(3);
	m_transform.setAnchor(0.5, 0.5);
}

void EnemiesPiranhaPlant::onCollisionEnter(Collision& col, const Direction& side)
{
	    if (col.m_entity->isType<Mario>()) {
        if (side == Direction::UP) {
			mIsMarioOnTop = true;
        }
    }
	
}

void EnemiesPiranhaPlant::update()
{
	const auto posMario = mMario.getPos();
	auto Post = m_transform.getPosition();

	if(!(mIsMarioOnTop && mState == HIDDEN)) {
		
		mTimeCnt++;
	}
	mIsMarioOnTop = false;
	
	switch (mState) {
	case HIDDEN: {
		if (mTimeCnt >= TIME_HIDE) {
			mState = SHOWING;
			mTimeCnt = 0;
			 m_anim.loadFromJsonFile("Resources/Animations/Fireball.json");
			 setHide(false);
		}	
		break;
	}
	case SHOW: {
		if (mTimeCnt >= TIME_SHOW) {
			mState = HIDING;
			mTimeCnt = 0;
			m_anim.loadFromJsonFile("Resources/Animations/Fireball.json");
			setHide(false);
		}	
		break;
	}
	case HIDING: {
		if (mTimeCnt >= TIME_HIDE) {
			mState = HIDDEN;
			mTimeCnt = 0;
			setHide(true);
		}	
		break;
	} 
	case SHOWING: {
		if (mTimeCnt >= TIME_SHOWING) {
				mState = SHOW;
				mTimeCnt = 0;
				m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
				setHide(false);
			}
		m_transform.setPosition(Post.x, Post.y - 0.01);	
		break;
	}
	default:
		break;
	}
	//if(mState == HIDDEN) {
	//	setHide(true);
	//}
	//else {
	//	setHide(false);
	//}
	// if( mState == SHOWING) {
	// 	m_transform.setPosition(Post.x, Post.y - 0.01);
	// }
	if (mState == SHOWING || mState == HIDING) {
		//m_anim.loadFromJsonFile("Resources/Animations/Fireball.json");
	}
	else {
		//m_anim.loadFromJsonFile("Resources/Animations/Coin.json");

	}
}

EnemiesPiranhaPlant::State EnemiesPiranhaPlant::getState()
{
	return mState;
}

void EnemiesPiranhaPlant::setHide(bool isHide)
{
	//std::cout << "Hide: " << isHide << '\n';
	m_sprite.setEnable(!isHide);
	getComponent<Collision>().setTrigger(isHide);
}
