#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include "Transform2D.hpp"
#include "Line.hpp"
#include "GameManager.hpp"
#include <vector>
#include <iostream>
using namespace std;

class Handle : public GUI {
private:
	Vector2f m_dragPos;
	CircleShape m_handleShape;

public:
	Handle(Object* parent = nullptr);
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
	vector<void (*)(T)> m_listeners;

public:
	Slider(Object* parent = nullptr) : GUI(parent) {
		m_handle.getComponent<Transform2D>().setPosition(m_transform.getPosition());
		m_value = 0;
		m_minVal = 0;
		m_maxVal = 0;
		m_handle.setRenderOrder(6);
		setRenderOrder(5);
	}

	Slider(T minVal, T maxVal, T width, T val = 0, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr) : GUI(parent), m_minVal(minVal), m_maxVal(maxVal), m_value(val), m_handle(this) {
		m_transform.setPosition(pos);
		m_transform.getRect() = { pos.x, pos.y, width, 1 };
		m_handle.setRenderOrder(6);
		setRenderOrder(5);

		m_background.setSize({ width, 2 });
		m_fillArea.setSize({ width, 2 });

		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));

		m_background.setOutlineThickness(1);
		m_background.setOutlineColor(Color(150, 150, 150));

		m_background.setFillColor(Color(150, 150, 150));
		m_fillArea.setFillColor(Color(50, 50, 50));
	}

	~Slider() {

	}

	void setPostion(const sf::Vector2f& position)
	{
		m_transform.setPosition(position);
		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));
	}


	void update() override {
		if (m_handle.isOnDrag()) {
			Vector2f dragPos = m_handle.getDragPos();
			if (dragPos.x < m_transform.left) dragPos.x = m_transform.left;
			if (dragPos.x > m_transform.right) dragPos.x = m_transform.right;

			T tempVal = (dragPos.x - m_transform.left) / m_transform.width * (m_maxVal - m_minVal) + m_minVal;

			if (tempVal != m_value) {
				m_value = tempVal;
				for (auto& i : m_listeners)
					i(m_value);
			}

			m_handle.getComponent<Transform2D>().setPosition({ dragPos.x - m_transform.left, 0 });
		}

		m_fillArea.setScale({ (T)m_value / (m_maxVal - m_minVal), 1 });
	}

	void render() override {
		GameManager::getInstance()->getRenderWindow().draw(m_background);
		GameManager::getInstance()->getRenderWindow().draw(m_fillArea);
	}

	T getValue() {
		return m_value;
	}

	void addListener(void (*listener)(T)) {
		m_listeners.push_back(listener);
	}

	void removeListener(void (*listener)(T)) {
		m_listeners.erase(remove_if(m_listeners.begin(), m_listeners.end(),
			[](const void (*&item)(T)) {
				return item == listener;
			}),
			m_listeners.end());
	}

	void removeAllListeners() {
		m_listeners.clear();
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
};