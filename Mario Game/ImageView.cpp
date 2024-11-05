#include "ImageView.hpp"
#include <iostream>

ImageView::ImageView(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        std::cerr << "Error loading image\n";
    }
    sprite.setTexture(texture);

 
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = 160.0f / textureSize.x; // this scale is just random to so i can demo easier, the mario should be 16x16 pixel as we discuss earlier but right now i want to make it easy to prove that i can view image
    float scaleY = 160.0f / textureSize.y; // this scale is just random to so i can demo easier, the mario should be 16x16 pixel as we discuss earlier but right now i want to make it easy to prove that i can view image
    sprite.setScale(scaleX, scaleY);
}

void ImageView::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
