#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include "Transform2D.hpp"
#include "Line.hpp"
#include <iostream>

class Handle : public GUI {
private:
	Vector2f m_dragPos;
	CircleShape m_handleShape;

public:
	Handle();
	Handle(RenderWindow& window, Object* parent = nullptr);
	~Handle();

	void update() override;
	void render() override;
	void onDrag(const Vector2f& mousePos) override;
	const Vector2f& getDragPos();
	void setColor(const Color& color);
	void setOutlineColor(const Color& color);
	void setThickness(float thickness);
};

template<typename T>
class Slider : public GUI {
private:
	T m_value;
	T m_minVal;
	T m_maxVal;
	Handle m_handle;
	RectangleShape m_background;
	RectangleShape m_fillArea;

public:
	Slider(Object* parent = nullptr) : m_value(0), m_minVal(0), m_maxVal(1) {
		m_handle.getComponent<Transform2D>().setPosition(m_transform.getPosition());
		m_parent = parent;
	}

	Slider(RenderWindow& window, const T& minVal, const T& maxVal, const T& val = 0, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr) : m_minVal(minVal), m_maxVal(maxVal), m_value(val), m_handle(window, this) {
		m_window = &window;
		m_parent = parent;
		m_transform.setPosition(pos);
		m_transform.getRect() = { pos.x, pos.y, maxVal, 10 };

		m_background.setSize({ maxVal, 5 });
		m_fillArea.setSize({ maxVal, 5 });

		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));

		m_background.setOutlineThickness(2);
		m_background.setOutlineColor(Color(150, 150, 150));

		m_background.setFillColor(Color(150, 150, 150));
		m_fillArea.setFillColor(Color(50, 50, 50));
	}

	Slider(const Slider& slider) {

	}

	~Slider() {

	}

	void update() override {
		Vector2f dragPos = m_handle.getDragPos();
		if (dragPos.x < m_transform.getRect().left) dragPos.x = m_transform.getRect().left;
		if (dragPos.x > m_transform.getRect().right) dragPos.x = m_transform.getRect().right;
		m_value = dragPos.x - m_transform.getRect().left;
		m_handle.getComponent<Transform2D>().setPosition({ dragPos.x - m_transform.getRect().left, m_handle.getComponent<Transform2D>().getPosition().y });
		m_fillArea.setScale({ m_value / m_transform.getRect().width, 1 });

		m_window->draw(m_background);
		m_window->draw(m_fillArea);
	}

	void setBackgroundColor(const Color& color) {
		m_background.setFillColor(color);
	}

	void setBgOutlineColor(const Color& color) {
		m_background.setOutlineColor(color);
	}

	void setBgThickness(float thickness) {
		m_background.setOutlineThickness(thickness);
	}

	void setFillAreaColor(const Color& color) {
		m_fillArea.setFillColor(color);
	}

	void setFillAreaOutlineColor(const Color& color) {
		m_fillArea.setOutlineColor(color);
	}

	void setFillAreaThickness(float thickness) {
		m_fillArea.setOutlineThickness(thickness);
	}

	void setHandleColor(const Color& color) {
		m_handle.setColor(color);
	}

	void setHandleOutlineColor(const Color& color) {
		m_handle.setOutlineColor(color);
	}

	void setHandleThickness(float thickness) {
		m_handle.setThickness(thickness);
	}

	T getCurrentValue()
	{
		return m_value;
	}
};