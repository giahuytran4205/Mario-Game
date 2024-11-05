#include "InputField.hpp"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

InputField::InputField(float x, float y, float width, float height) {
    if (!font.loadFromFile("Font/arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    // Initialize the text box (not displayed, but we'll keep it for event handling)
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);

    // Initialize the text
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + 5);
}

void InputField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        // Check if the returned key code is -1, assuming it's Caps Lock if so
        if (event.key.code == -1) {
            std::cout << "Caps Lock pressed" << std::endl;
            return;
        }

        switch (event.key.code) {
        case sf::Keyboard::Backspace:
            std::cout << "Backspace pressed" << std::endl;
            break;
        case sf::Keyboard::Delete:
            std::cout << "Delete pressed" << std::endl;
            break;
        case sf::Keyboard::Enter:
            std::cout << "Enter pressed" << std::endl;
            break;
        case sf::Keyboard::Tab:
            std::cout << "Tab pressed" << std::endl;
            break;
        case sf::Keyboard::Space:
            std::cout << "Space pressed" << std::endl;
            break;
        case sf::Keyboard::LControl: case sf::Keyboard::RControl:
            std::cout << "Control pressed" << std::endl;
            break;
        case sf::Keyboard::LShift: case sf::Keyboard::RShift:
            std::cout << "Shift pressed" << std::endl;
            break;
        case sf::Keyboard::LAlt: case sf::Keyboard::RAlt:
            std::cout << "Alt pressed" << std::endl;
            break;
        case sf::Keyboard::Escape:
            std::cout << "Escape pressed" << std::endl;
            break;
        case sf::Keyboard::Left:
            std::cout << "Left Arrow pressed" << std::endl;
            break;
        case sf::Keyboard::Right:
            std::cout << "Right Arrow pressed" << std::endl;
            break;
        case sf::Keyboard::Up:
            std::cout << "Up Arrow pressed" << std::endl;
            break;
        case sf::Keyboard::Down:
            std::cout << "Down Arrow pressed" << std::endl;
            break;
            // Function keys F1 through F12
        case sf::Keyboard::F1: std::cout << "F1 pressed" << std::endl; break;
        case sf::Keyboard::F2: std::cout << "F2 pressed" << std::endl; break;
        case sf::Keyboard::F3: std::cout << "F3 pressed" << std::endl; break;
        case sf::Keyboard::F4: std::cout << "F4 pressed" << std::endl; break;
        case sf::Keyboard::F5: std::cout << "F5 pressed" << std::endl; break;
        case sf::Keyboard::F6: std::cout << "F6 pressed" << std::endl; break;
        case sf::Keyboard::F7: std::cout << "F7 pressed" << std::endl; break;
        case sf::Keyboard::F8: std::cout << "F8 pressed" << std::endl; break;
        case sf::Keyboard::F9: std::cout << "F9 pressed" << std::endl; break;
        case sf::Keyboard::F10: std::cout << "F10 pressed" << std::endl; break;
        case sf::Keyboard::F11: std::cout << "F11 pressed" << std::endl; break;
        case sf::Keyboard::F12: std::cout << "F12 pressed" << std::endl; break;
            // Printable ASCII characters (A to Z and 0 to 9)
        default:
            if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                // Map the key code to its corresponding ASCII letter
                char typedChar = static_cast<char>('A' + event.key.code - sf::Keyboard::A);
                // Adjust for lowercase if Shift is not pressed
                if (!event.key.shift) {
                    typedChar = std::tolower(typedChar);
                }
                std::cout << "Typed character: " << typedChar << std::endl;
            }
            else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9) {
                char typedChar = static_cast<char>('0' + event.key.code - sf::Keyboard::Num0);
                std::cout << "Typed character: " << typedChar << std::endl;
            }
            else {
                // Default message for any unmapped key code
                std::cout << "Key pressed: " << event.key.code << std::endl;
            }
            break;
        }
    }
}

void InputField::draw(sf::RenderWindow& window) {
    // No drawing needed since we are hiding the input box in the SFML window
}
