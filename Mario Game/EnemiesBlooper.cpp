#include "EnemiesBlooper.h"

EnemiesBlooper::EnemiesBlooper(Mario& mario, Object* parent) : mMario(mario)
{
    m_transform.setSize(16, 16);
    m_anim.loadFromJsonFile("Resources/Animations/Coin.json");
    m_sprite.setParent(this);
    m_sprite.getComponent<Transform2D>().setAnchor(0.5, 0.5);
    m_sprite.setRenderOrder(3);
    m_transform.setAnchor(0.5, 0.5);

}

EnemiesBlooper::~EnemiesBlooper()
{
}

void EnemiesBlooper::onCollisionEnter(Collision& col, const Direction& side)
{
}

void EnemiesBlooper::hit(bool isDestroy)
{
}

void EnemiesBlooper::update()
{
    if (mTimeUpdate > 50) {
        auto lastPost = m_transform.getLastPosition();
        const auto posMario = mMario.getPos();

        int randomX = std::rand() % 17 - 8;
        int randomY = std::rand() % 31 - 15;

        if (lastPost.y + randomY > 0 || (lastPost.y + randomY < 260)) {
            randomY = -randomY;
        }

        auto const Distance = std::abs(lastPost.x - posMario.x);
        if (Distance < 150) {
            if ((lastPost.x - posMario.x) * randomX > 0) {
                randomX = -randomX;
            }
            if ((lastPost.y - posMario.y) * randomY > 0) {
                randomY = -randomY;
            }
        }
        std::cout << "lastPost.x " << lastPost.x << " lastPost.x " << posMario.x << "\n";

        Vector2f move(randomX, randomY);




        m_transform.move(move);
        mTimeUpdate = 0;
    }
    mTimeUpdate++;

}
