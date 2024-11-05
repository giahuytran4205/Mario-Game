
#ifndef INPUTFIELD_HPP
#define INPUTFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string>

class InputField {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;
    std::string input;

public:
    InputField(float x, float y, float width, float height);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
};

#endif // INPUTFIELD_HPP
