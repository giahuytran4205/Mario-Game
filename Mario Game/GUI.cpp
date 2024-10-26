#include "GUI.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "GameManager.hpp"
#include "Rect.hpp"
#include "Transform2D.hpp"
#include <iostream>
using namespace sf;

GUI::GUI() : m_background(m_sprite), m_window(&GameManager::getInstance()->getRenderWindow()) {
	m_parent = nullptr;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isInteractable = true;
	EventSystem::m_instance->addListener(this);
}

GUI::GUI(const gr::Rect& rect, RenderWindow* window, Object* parent) : m_background(m_sprite), m_window(window) {
	m_parent = parent;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isInteractable = true;
	m_transform.getRect() = rect;
}

GUI::GUI(float left, float top, float width, float height, RenderWindow* window, Object* parent) : m_background(m_sprite), m_window(window) {
	m_parent = parent;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isInteractable = true;
	m_transform.getRect() = {left, top, width, height};
}

GUI::~GUI() {

}

void GUI::onSelected() {}
void GUI::onDeselect() {}
void GUI::onPressed() {}
void GUI::onHovered() {}
void GUI::onClick() {}

void GUI::update() {
	Sprite& sprite = m_sprite.getSprite();
	sprite.setScale({ m_transform.getRect().width / sprite.getTexture()->getSize().x, m_transform.getRect().height / sprite.getTexture()->getSize().y });
}

void GUI::handleEvent(const Event& event) {
	if (isInteractable()) {
		if (m_transform.getRect().contains((Vector2f)Mouse::getPosition(*m_window))) {
			m_isHovered = true;
			onHovered();

			if (event.type == sf::Event::Closed) {
				m_window->close();
			}

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				m_isPressed = true;
				onPressed();
			}

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				m_isPressed = false;
				m_isSelected = !m_isSelected;
				onClick();
			}
		}
		else
			m_isHovered = false;

		if (isSelected())
			onSelected();
		else
			onDeselect();
	}
}

void GUI::render() {

}

bool GUI::isSelected() {
	return m_isSelected;
}

bool GUI::isPressed() {
	return m_isPressed;
}

bool GUI::isHovered() {
	return m_isHovered;
}

bool GUI::isInteractable() {
	return m_isInteractable;
}

void GUI::setSelect(bool isSelect) {
	m_isSelected = isSelect;
}

void GUI::setInteractable(bool isInteractable) {
	m_isInteractable = isInteractable;
}