#pragma once

#include "Common.hpp"
#include "GUI.hpp"
#include "TextView.hpp"
#include "SFML/Graphics.hpp"

/*
When button is not hovered (set Default):
	- Color of text is a color != white
	- Texture is m_notHoveredTexture
When button is hovered (call onHovered()):
	- Color of text is white
	- Texture is m_hoveredTexture
When button is pressed (call onPressed()): 
	- Color of text is a color != white & color != default color
	- Texture is m_pressedTexture
	- Scale background's sprite to 0.95 (Reduce very small to just for User know)
When button is released (call onClicked()) == When button is not hovered (set Default)
*/

class Button : public GUI
{
private:
	sf::Texture m_defaultTexture;
	sf::Texture m_hoveredTexture;
	sf::Texture m_pressedTexture;
	TextView* m_text;
	void (*m_action) ();

public:
	Button(sf::RenderWindow& window,const sf::Texture& defaultTexture, const sf::Texture& hoveredTexture, const sf::Texture& pressedTexture, const sf::Text text, const sf::Font font, void (*action) () = nullptr, Object* parent = nullptr);
	// Ex: Button button(window, defaultTexture, hoveredTexture, pressedTexture, text, allFonts["Arial"], action, parent);
	Button(sf::RenderWindow& window, const sf::Texture& texture, const sf::Text text, const sf::Font font, void (*action) () = nullptr, Object* parent = nullptr); // defaultTexture == hoveredTexture == pressedTexture
	// Ex: Button button(window, texture, text, allFonts["Arial"], action, parent);
	~Button();

	void setDefaultTexture(const Texture& defaultTexture);
	void setHoveredTexture(const Texture& hoveredTexture);
	void setPressedTexture(const Texture& pressedTexture);

	void setFont(const sf::Font& font);
	void setText(const sf::Text& text);

	void onHovered() override;
	void onPressed() override;
	void onClick() override;

	void setAction(void (*func) ());
};
