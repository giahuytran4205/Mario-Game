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

GUI::GUI() : m_window(&GameManager::getInstance()->getRenderWindow()) {
	m_parent = nullptr;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isOnDrag = false;
	m_isInteractable = true;
	m_background.setParent(this);
	EventSystem::m_instance->addListener(this);
}

GUI::GUI(const FRect& rect, RenderWindow* window, Object* parent) : m_background(parent), m_window(window) {
	m_parent = parent;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isOnDrag = false;
	m_isInteractable = true;
	m_transform.getRect() = rect;
}

GUI::GUI(float left, float top, float width, float height, RenderWindow* window, Object* parent) : m_background(parent), m_window(window) {
	m_parent = parent;
	m_isSelected = false;
	m_isPressed = false;
	m_isHovered = false;
	m_isOnDrag = false;
	m_isInteractable = true;
	m_transform.getRect() = {left, top, width, height};
}

GUI::~GUI() {

}

void GUI::onSelected() {}
void GUI::onDeselect() {}
void GUI::onPressed() {}
void GUI::onHovered() {}
void GUI::onUnhovered() {}
void GUI::onClick() {}
void GUI::onKeyPressed(const sf::Event& event) {}
void GUI::onDrag(const Vector2f& mousePos) {}

void GUI::update() {
	Sprite& sprite = m_background;
	if (sprite.getTexture() && sprite.getTexture()->getSize().x != 0 && sprite.getTexture()->getSize().y != 0)
		sprite.setScale({ m_transform.getRect().width / sprite.getTexture()->getSize().x, m_transform.getRect().height / sprite.getTexture()->getSize().y });
}


void GUI::handleEvent(const Event& event) {
	if (isInteractable()) {
		Vector2f dist = m_window->getView().getCenter() - m_window->getDefaultView().getCenter();

		if (m_transform.getRect().contains((Vector2f)Mouse::getPosition(*m_window) + dist)) {
			m_isHovered = true;
			onHovered();

			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
				m_isPressed = true;
				m_isOnDrag = true;
				onPressed();
			}

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
				m_isPressed = false;
				m_isOnDrag = false;
				m_isSelected = true;
				onClick();
			}
		}
		else {
			if (isHovered()) onUnhovered();
			m_isHovered = false;
			m_isSelected = false;
		}
		
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			m_isOnDrag = false;

		if (event.type == Event::TextEntered) {
			onKeyPressed(event);
		}

		if (isOnDrag() && event.type == Event::MouseMoved) {
			onDrag((Vector2f)Mouse::getPosition(*m_window) + dist);
		}

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

bool GUI::isOnDrag() {
	return m_isOnDrag;
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