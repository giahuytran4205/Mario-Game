#pragma once
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"
#include "Mario.hpp"
#include "Block.hpp"

class EnemiesBuzzyBeetle : public Enemy {
public:
    EnemiesBuzzyBeetle(Object* parent = nullptr);
    ~EnemiesBuzzyBeetle();

    void onCollisionEnter(Collision& col, const Direction& side) override;
    void update() override;
	void die();
};
