#pragma once
#include "Enum.hpp"
#include "Common.hpp"
#include "SpriteRenderer.hpp"
#include "Transform2D.hpp"
#include "Rect.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include <map>

class TextView : public Object, public sf::Text {
private:
	void wrapText();

	FRect m_table;

public:
	TextView(Object* parent = nullptr);
	TextView(const FRect& table, const std::string& content, const sf::Font& font, Object* parent = nullptr);
	~TextView();

	void configure(const FRect& table, const std::string& content, const sf::Font& font);

	void setTable(const FRect& table);
	const FRect& getTable() const;
	void render() override;
};