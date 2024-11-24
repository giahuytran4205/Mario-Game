#pragma once
#include "SFML/Graphics.hpp"

class FRect : public sf::Rect<float> {
private:
	sf::Vector2f m_center;
	sf::Vector2f m_anchor;

public:
	float right, bottom;

	FRect();
	FRect(float left, float top, float width, float height);
	~FRect();

	sf::Vector2f getCenter() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getAnchor() const;
	bool pointOverlap(const sf::Vector2f& point) const;
	void setPosition(const sf::Vector2f& pos);
	void setCenter(const sf::Vector2f& center);
	void setAnchor(const sf::Vector2f& anchor);
	void setSize(const sf::Vector2f& size);
};