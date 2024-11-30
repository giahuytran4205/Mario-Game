#pragma once
#include "SFML/Graphics.hpp"

class FRect : public sf::Rect<float> {
protected:
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
	bool contains(const sf::Vector2f& point) const;
	int tangentSide(const FRect& rect) const;
	void setPosition(const sf::Vector2f& pos);
	void setPosition(float x, float y);
	void setCenter(const sf::Vector2f& center);
	void setCenter(float x, float y);
	void setAnchor(const sf::Vector2f& anchor);
	void setAnchor(float anchorX, float anchorY);
	void setSize(const sf::Vector2f& size);
	void setSize(float width, float height);
};