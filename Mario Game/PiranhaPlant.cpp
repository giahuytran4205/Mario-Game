/*
#include "EnemiesPiranhaPlant.h"
#include "AnimationFactory.hpp"
#include "CollisionManager.hpp"
#include "SpriteRenderer.hpp"
#include "Transform2D.hpp"

PiranhaPlant::PiranhaPlant() {
    // Initialize animations for biting and idle states
    AnimationFactory::createAnimation(this, "PiranhaPlant", 0); // Bite
    AnimationFactory::createAnimation(this, "PiranhaPlant", 1); // Idle

    currentState = 1; // Start with idle state
    setAnimationState(currentState);

    // Set collision properties
    setCollisionLayer(CollisionLayer::Enemy);
    setCollisionMask(CollisionLayer::Player);
}

void PiranhaPlant::update(float deltaTime) {
    // Update animation
    AnimationTrack::update(deltaTime);

    // Switch between states
    stateTimer -= deltaTime;
    if (stateTimer <= 0) {
        toggleState();
        stateTimer = stateDuration;
    }

    // Handle collisions
    auto collisions = CollisionManager::getCollisions(this);
    for (auto& collision : collisions) {
        if (collision.other->getLayer() == CollisionLayer::Player) {
            onPlayerCollision();
        }
    }
}

void PiranhaPlant::toggleState() {
    currentState = (currentState == 0) ? 1 : 0;
    setAnimationState(currentState);
}

void PiranhaPlant::onPlayerCollision() {
    // Logic for when the player collides with the Piranha Plant
    // Damage player or handle interaction
    notifyCollisionEvent();
}

void PiranhaPlant::setAnimationState(int state) {
    AnimationTrack::play(state);
}

PiranhaPlant::~PiranhaPlant() {
    // Clean up resources
}
*/