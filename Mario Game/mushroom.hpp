#pragma once
#include "Item.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "Block.hpp"
#include "TextureManager.hpp"

enum class MushroomType {
    ORANGE,  // Nấm cam
    GREEN    // Nấm xanh
};

class Mushroom : public Item {
private:
    float m_speed = 0.2f;
    bool m_onWall = false;
    MushroomType m_type;
    SoundComponent& m_sound;

public:
    Mushroom(MushroomType type, Object* parent = nullptr);
    ~Mushroom();

    void onCollisionEnter(Collision& col, const Direction& side) override;
    void update() override;
};