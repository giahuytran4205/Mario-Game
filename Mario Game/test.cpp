#include <SFML/Graphics.hpp>
#include "InputField.hpp"
#include "ImageView.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    InputField inputField(50, 500, 300, 30); // The input field is created but not drawn
    ImageView imageView("Resources/blocks.png");        // Path to the image file to load

    std::cout << "Type in the terminal; input will not appear in the window." << std::endl;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Process input events, but do not display the input box, watch the result on the terminal
            inputField.handleEvent(event);
        }

        window.clear();

        // Draw the image
        imageView.draw(window);

        window.display();
    }

    return 0;
}
