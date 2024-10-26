#include "Rect.hpp"
#include "SFML/Graphics.hpp"

namespace gr {
	Rect::Rect() {
		left = top = right = bottom = 0;
		width = height = 0;
		center = { 0, 0 };
	}

	Rect::Rect(float left, float top, float width, float height) {
		this->left = left;
		this->top = top;
		this->width = width;
		this->height = height;
		right = left + width;
		bottom = top + height;
		center = { left + width / 2, top + height / 2 };
	}

	Rect::~Rect() {

	}

	bool Rect::pointOverlap(const sf::Vector2f& point) const {
		return (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
	}

	void Rect::setPosition(const sf::Vector2f& pos) {
		left = pos.x - width / 2;
		top = pos.y - height / 2;
		right = left + width;
		bottom = top + height;
	}
}