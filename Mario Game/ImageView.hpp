#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP

#include <SFML/Graphics.hpp>
#include <string>

class ImageView {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    ImageView(const std::string& filePath);
    void draw(sf::RenderWindow& window);
};

#endif // IMAGEVIEW_HPP
