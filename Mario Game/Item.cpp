#include "Item.hpp"
#include <iostream>

// GreenMushroom implementation
GreenMushroom::GreenMushroom() {
    animationFrames.push_back({ "green_mushroom_1.png", 100 }); // this image will be dealt with later
    animationFrames.push_back({ "green_mushroom_2.png", 100 }); // this image will be dealt with later

    if (!texture.loadFromFile(animationFrames[currentFrameIndex].texturePath)) {
        std::cerr << "Failed to load green_mushroom texture\n";
    }
    sprite.setTexture(texture);
}

void GreenMushroom::update(int deltaTime) {
    sprite.move(speed * deltaTime, 0);
    /*
    updateAnimation(deltaTime);
    */
}

void GreenMushroom::onCollision() {
    speed = -speed;
}

// OrangeMushroom implementation
OrangeMushroom::OrangeMushroom() {
    animationFrames.push_back({ "orange_mushroom_1.png", 100 });// this image will be dealt with later
    animationFrames.push_back({ "orange_mushroom_2.png", 100 });// this image will be dealt with later

    if (!texture.loadFromFile(animationFrames[currentFrameIndex].texturePath)) {
        std::cerr << "Failed to load orange_mushroom texture\n";
    }
    sprite.setTexture(texture);
}

void OrangeMushroom::update(int deltaTime) {
    sprite.move(speed * deltaTime, 0);
    /*
    updateAnimation(deltaTime);
    */
}

void OrangeMushroom::onCollision() {
    speed = -speed;
}

// TurtleShell implementation
TurtleShell::TurtleShell() {
    animationFrames.push_back({ "turtle_shell_1.png", 150 });// this image will be dealt with later
    animationFrames.push_back({ "turtle_shell_2.png", 150 });// this image will be dealt with later

    if (!texture.loadFromFile(animationFrames[currentFrameIndex].texturePath)) {
        std::cerr << "Failed to load turtle_shell texture\n";
    }
    sprite.setTexture(texture);
}

void TurtleShell::update(int deltaTime) {
    /*
    if (playerKicksShell()) {
        sprite.move(speed * deltaTime, 0);
    }
    */
}

void TurtleShell::onCollision() {}

// Flower implementation
Flower::Flower() {
    animationFrames.push_back({ "flower_1.png", 120 });// this image will be dealt with later
    animationFrames.push_back({ "flower_2.png", 120 });// this image will be dealt with later

    if (!texture.loadFromFile(animationFrames[currentFrameIndex].texturePath)) {
        std::cerr << "Failed to load flower texture\n";
    }
    sprite.setTexture(texture);
}

void Flower::update(int deltaTime) {
    /*
    if (hiddenPosition < finalPosition) {
        sprite.move(0, -0.05f * deltaTime);
    }
    */
}

void Flower::onCollision() {}

// Axe implementation
Axe::Axe() {
    animationFrames.push_back({ "axe_1.png", 130 });// this image will be dealt with later
    animationFrames.push_back({ "axe_2.png", 130 });// this image will be dealt with later

    if (!texture.loadFromFile(animationFrames[currentFrameIndex].texturePath)) {
        std::cerr << "Failed to load axe texture\n";
    }
    sprite.setTexture(texture);
}

void Axe::update(int deltaTime) {
    // No specific logic for now
}

void Axe::onCollision() {}

// Star implementation
Star::Star() {
    animationFrames.push_back({ "star_1.png", 80 });// this image will be dealt with later
    animationFrames.push_back({ "star_2.png", 80 });// this image will be dealt with later

    if (!texture.loadFromFile(animationFrames[currentFrameIndex].texturePath)) {
        std::cerr << "Failed to load star texture\n";
    }
    sprite.setTexture(texture);
}

void Star::update(int deltaTime) {
    /*
    if (distanceToMario < threshold) {
        sprite.move(speed * deltaTime, 0);
    } else {
        sprite.move(-speed * deltaTime, 0);
    }
    */
}

void Star::onCollision() {}
