#ifndef ITEM_HPP
#define ITEM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

// Frame struct for animation
struct Frame {
    std::string texturePath;
    int duration; // in milliseconds
};

// Base Item class
class Item {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed = 0.1f; // Default speed for moving items

    // Animation management
    std::vector<Frame> animationFrames; // Holds frames of animation
    int currentFrameIndex = 0;
    int elapsedTime = 0;

public:
    virtual ~Item() = default;
    virtual void update(int deltaTime) = 0;
    virtual void onCollision() = 0;

    void setPosition(float x, float y) { sprite.setPosition(x, y); }
    void draw(sf::RenderWindow& window) { window.draw(sprite); }

    // Placeholder for animation logic
    /*
    void updateAnimation(int deltaTime) {
        elapsedTime += deltaTime;
        if (elapsedTime >= animationFrames[currentFrameIndex].duration) {
            elapsedTime = 0;
            currentFrameIndex = (currentFrameIndex + 1) % animationFrames.size();
            texture.loadFromFile(animationFrames[currentFrameIndex].texturePath);
            sprite.setTexture(texture);
        }
    }
    */
};

class GreenMushroom : public Item {
public:
    GreenMushroom();
    void update(int deltaTime) override;
    void onCollision() override;
};

class OrangeMushroom : public Item {
public:
    OrangeMushroom();
    void update(int deltaTime) override;
    void onCollision() override;
};

class TurtleShell : public Item {
public:
    TurtleShell();
    void update(int deltaTime) override;
    void onCollision() override;
};

class Flower : public Item {
public:
    Flower();
    void update(int deltaTime) override;
    void onCollision() override;
};

class Axe : public Item {
public:
    Axe();
    void update(int deltaTime) override;
    void onCollision() override;
};

class Star : public Item {
public:
    Star();
    void update(int deltaTime) override;
    void onCollision() override;
};

#endif // ITEM_HPP
