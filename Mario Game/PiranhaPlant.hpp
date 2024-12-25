/*
#pragma once

#include "Enemy.hpp"

class GameScene; // Forward declaration of GameScene

class PiranhaPlant : public Enemy {
public:
    PiranhaPlant(GameScene* parent);
    ~PiranhaPlant();

    void update(float deltaTime) override;

private:
    void toggleState();
    void onPlayerCollision();
    void setAnimationState(int state);

    int currentState;
    float stateTimer = 2.0f; // Duration before toggling state
    const float stateDuration = 2.0f;
    GameScene* parentScene; // Store a reference to the parent scene
};

*/