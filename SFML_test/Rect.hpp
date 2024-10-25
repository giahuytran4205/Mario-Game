#pragma once
#include "SFML/Graphics.hpp"

namespace gr {
	class Rect : public sf::Rect<float> {
	public:
		float right, bottom;
		sf::Vector2f center;

		Rect();
		Rect(float left, float top, float width, float height);
		~Rect();

		bool pointOverlap(const sf::Vector2f& point) const;
		void setPosition(const sf::Vector2f& pos);
	};
}