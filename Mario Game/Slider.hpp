#pragma once
#include "SFML/Graphics.hpp"
#include "GUI.hpp"
#include "Transform2D.hpp"
#include "Line.hpp"
#include <vector>
#include <iostream>
using namespace std;

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
	Vector2f m_scale;
	T m_value;
	T m_minVal;
	T m_maxVal;
	Handle m_handle;
	RectangleShape m_background;
	RectangleShape m_fillArea;
	vector<void (*)(T)> m_listeners;

public:
	Slider(Object* parent = nullptr) : m_value(0), m_minVal(0), m_maxVal(1), m_scale({1.0f, 1.0f}) {
		m_handle.getComponent<Transform2D>().setPosition(m_transform.getPosition());
		m_parent = parent;
	}

	Slider(RenderWindow& window, const T& minVal, const T& maxVal, const T& val = 0, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr)
		: m_minVal(minVal), m_maxVal(maxVal), m_value(val), m_handle(window, this) {
		m_window = &window;
		m_parent = parent;

		if (m_value < m_minVal) m_value = m_minVal;
		if (m_value > m_maxVal) m_value = m_maxVal;

		m_transform.setPosition(pos);
		float sliderWidth = maxVal;
		m_transform.getRect() = { pos.x, pos.y, sliderWidth, 10 };

		m_background.setSize({ sliderWidth, 5 });
		m_fillArea.setSize({ sliderWidth, 5 });

		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));

		m_background.setOutlineThickness(2);
		m_background.setOutlineColor(Color(150, 150, 150));
		m_background.setFillColor(Color(150, 150, 150));
		m_fillArea.setFillColor(Color(50, 50, 50));

		float normalizedValue = (m_value - m_minVal) / (m_maxVal - m_minVal);
		float handleX = m_transform.getRect().left + normalizedValue * sliderWidth;
		m_handle.getComponent<Transform2D>().setPosition({ handleX, m_transform.getWorldPosition().y });

		float fillWidth = normalizedValue * sliderWidth;
		m_fillArea.setScale({ fillWidth / m_fillArea.getSize().x, 1.0f });
	}

	void init(RenderWindow& window, const T& minVal, const T& maxVal, const T& val = 0, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr) {
		m_window = &window;
		m_parent = parent;

		m_minVal = minVal;
		m_maxVal = maxVal;
		m_value = val;

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

		float scaledLeft = m_transform.getRect().left * m_scale.x;
		float handleX = scaledLeft + (m_value - m_minVal) / (m_maxVal - m_minVal) * m_transform.getRect().width * m_scale.x;
		m_handle.getComponent<Transform2D>().setPosition({ handleX, m_transform.getWorldPosition().y });

		float fillWidth = (m_value - m_minVal) / (m_maxVal - m_minVal);
		m_fillArea.setScale({ fillWidth * m_scale.x, 1.0f });
	}

	~Slider() {

	}

	void update() override {
		Vector2f dragPos = m_handle.getDragPos();

		float scaledLeft = m_transform.getRect().left * m_scale.x;
		float scaledRight = m_transform.getRect().right * m_scale.x;

		if (dragPos.x < scaledLeft) dragPos.x = scaledLeft;
		if (dragPos.x > scaledRight) dragPos.x = scaledRight;

		T tempVal = (dragPos.x - scaledLeft) / (scaledRight - scaledLeft) * (m_maxVal - m_minVal) + m_minVal;

		if (tempVal != m_value) {
			m_value = tempVal;
			for (auto& i : m_listeners)
				i(m_value);
		}

		float handleX = scaledLeft + m_value * m_transform.getRect().width * m_scale.x;
		m_handle.getComponent<Transform2D>().setPosition({ handleX, m_handle.getComponent<Transform2D>().getPosition().y });

		float fillWidth = m_value / m_transform.getRect().width;
		m_fillArea.setScale({ fillWidth * m_scale.x, 1.0f });
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

	void setScale(const Vector2f& scale) {
		m_scale = scale;

		m_background.setSize({ m_transform.getRect().width * scale.x, 5 * scale.y });
		m_fillArea.setSize({ m_transform.getRect().width * scale.x, 5 * scale.y });

		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));

		float handleRadius = 10 * scale.x;
		m_handle.setThickness(handleRadius * 0.2f);

		float normalizedValue = (m_value - m_minVal) / (m_maxVal - m_minVal);
		float scaledLeft = m_transform.getRect().left * scale.x;
		float handleX = scaledLeft + normalizedValue * m_transform.getRect().width * scale.x;
		m_handle.getComponent<Transform2D>().setPosition({ handleX, m_transform.getWorldPosition().y });

		float fillWidth = normalizedValue * m_transform.getRect().width * scale.x;
		m_fillArea.setScale({ fillWidth / m_fillArea.getSize().x, 1.0f });
	}

	Vector2f getPosition() const {
		return m_transform.getWorldPosition();
	}

	void setPosition(const Vector2f& position) {
		m_transform.setPosition(position);

		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));

		float scaledLeft = m_transform.getRect().left * m_scale.x;
		float handleX = scaledLeft + m_value * m_transform.getRect().width * m_scale.x;
		m_handle.getComponent<Transform2D>().setPosition({ handleX, m_transform.getWorldPosition().y });
	}

	Vector2f getSize() const {
		return m_background.getSize();
	}

	void setSize(const Vector2f& size) {
		m_transform.getRect().width = size.x;
		m_transform.getRect().height = size.y;

		m_background.setSize({ size.x, 5 });
		m_fillArea.setSize({ size.x, 5 });

		m_background.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_background.getSize().y / 2));
		m_fillArea.setPosition(m_transform.getWorldPosition() - Vector2f(0, m_fillArea.getSize().y / 2));

		float normalizedValue = (m_value - m_minVal) / (m_maxVal - m_minVal);
		float handleX = m_transform.getRect().left + normalizedValue * size.x;
		m_handle.getComponent<Transform2D>().setPosition({ handleX, m_transform.getWorldPosition().y });

		float fillWidth = normalizedValue * size.x;
		m_fillArea.setScale({ fillWidth / m_fillArea.getSize().x, 1.0f });
	}
};