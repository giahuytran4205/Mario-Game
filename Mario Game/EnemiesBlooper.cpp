#include "EnemiesBlooper.h"

EnemiesBlooper::EnemiesBlooper(Mario& mario, Object* parent): 
    Enemy(parent, false), mMario(mario)
{
	m_transform.setSize(16, 16);
	m_anim.loadFromJsonFile("Resources/Animations/blooper.json");
    m_anim.play(0);
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);

    m_physics.setEnableGravity(false);
}

EnemiesBlooper::~EnemiesBlooper()
{
}

void EnemiesBlooper::onCollisionEnter(Collision& col, const Direction& side)
{
    if (col.m_entity->isDerivedFrom<Projectile>()) {
        destroy();
    }


    if (side == Direction::UP) {
        m_sound.play(SoundTrack::STOMP);
        destroy();
        col.m_entity->convertTo<Mario>()->getComponent<Physics2D>().setBaseVelocityY(-0.1f);
    }
    else {
        col.m_entity->convertTo<Mario>()->dead();
    }
}

void EnemiesBlooper::hit(bool isDestroy)
{
}

void EnemiesBlooper::update()
{
    if (m_autoControl.isControlled())
        return;
    const auto PosMario = mMario.getPos();
    const auto Post = m_transform.getPosition();
    const auto Distance = std::abs(PosMario.x - Post.x);
    if (!mIsActive) {
        mIsActive = Distance < 200;
    }

    if (!mIsActive)
        return;

    if (Distance > RANGE_FLOW_MARIO) {
        const auto newX = Post.x + ((Post.x > PosMario.x) ? (-1.0 * RANGE_STEP) : RANGE_STEP);
        const auto newY = Post.y + ((Post.y > PosMario.y) ? (-1.0 * RANGE_STEP) : RANGE_STEP);
        m_autoControl.addMoveByPoint({ float(newX), float(newY)}, 500, {0,0});
    }
    else {
        int radomStep = randRange<int>(-RANGE_FLOW_MARIO, RANGE_FLOW_MARIO);
        const auto newX = Post.x + radomStep;
        const auto newY = Post.y + radomStep;
        m_autoControl.addMoveByPoint({ float(newX), float(newY) }, 500, { 0,0 });

    }

    


    //if (mTimeUpdate > 50) {
    //    auto lastPost = m_transform.getLastPosition();
    //    const auto posMario = mMario.getPos();

    //    int randomX = std::rand() % 17 - 8;
    //    int randomY = std::rand() % 31 - 15;

    //    if (lastPost.y + randomY > 0 || (lastPost.y + randomY < 260)) {
    //        randomY = -randomY;
    //    }

    //    auto const Distance = std::abs(lastPost.x - posMario.x);
    //    if (Distance < 150) {
    //        if ((lastPost.x - posMario.x) * randomX > 0) {
    //            randomX = -randomX;
    //        }
    //    }
    //    std::cout << "lastPost.x " << lastPost.x << " lastPost.x " << posMario.x << "\n";

    //    Vector2f move(randomX, randomY);


    //   

    //    m_transform.move(move);
    //    mTimeUpdate = 0;
    //}
    //mTimeUpdate++;

}
