#pragma once
#include "Rect.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

constexpr float DEFAULT_RATIO_CHAR_SIZE_TABLE_HEIGHT = 1.0f;
constexpr int TEXTVIEW_DEFAUTL_RENDER_ORDER = 20;

class TextView : public Object, public sf::Text {
private:
	void wrapText();

	float m_ratioCharSizeTableHeight;

public:
	TextView(Object* parent = nullptr);
	TextView(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font, Object* parent = nullptr);
	~TextView();

	void configure(const sf::Vector2f& tablePosition, const sf::Vector2f& tableSize, const std::string& content, const sf::Font& font);

	void setRatioCharacterSizeTableHeight(float ratio);
	void setTable(const FRect& table);
	void setTablePosition(const sf::Vector2f& tablePosition);
	void setTableSize(const sf::Vector2f& tableSize);
	void alignLeft();
	void alignRight();
	void alignCenter();
	const FRect& getTable() const;
	void update() override;
	void render() override;
};