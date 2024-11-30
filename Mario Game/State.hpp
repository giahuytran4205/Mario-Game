#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class State {
public:
    virtual ~State() = default;
    virtual void init() = 0;
    virtual void handleEvents() = 0;
    virtual void update(float dT) = 0;
    virtual void render(float dT) = 0;
    virtual void resume();
    virtual void pause();
};

void fitBackground(sf::Sprite& sprite, sf::RenderWindow& window);