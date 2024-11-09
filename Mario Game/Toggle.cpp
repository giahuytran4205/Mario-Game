#include "Toggle.hpp"
#include "SFML/Graphics.hpp"
#include "ECS.hpp"
#include "GUI.hpp"
#include "Object.hpp"
#include "GameManager.hpp"
#include <iostream>
using namespace sf;

Toggle::Toggle() {}

Toggle::Toggle(RenderWindow& window, Texture& onTexture, Texture& offTexture, void (*action) (bool isOn), Object* parent)
	: m_onTexture(onTexture), m_offTexture(offTexture)
{
	m_window = &window;
	m_isOn = false;
	m_parent = parent;
	m_background.setTexture(m_offTexture);
	if (action) m_listeners.push_back(action);
}

Toggle::~Toggle() {

}

void Toggle::onClick() {
	m_isOn = !m_isOn;
	onTrigger();
}

void Toggle::setOnTexture(Texture& texture) {
	m_onTexture = texture;
}

void Toggle::setOffTexture(Texture& texture) {
	m_offTexture = texture;
}

void Toggle::onTrigger() {
	if (m_isOn)
		m_sprite.setTexture(m_onTexture);
	else
		m_sprite.setTexture(m_offTexture);

	for (auto& listener : m_listeners) {
		listener(m_isOn);
	}
}

void Toggle::addListener(void (*func) (bool isOn)) {
	if (func) m_listeners.push_back(func);
}

void Toggle::removeListener(void (*func) (bool isOn)) {
	auto it = find(m_listeners.begin(), m_listeners.end(), func);
	if (it != m_listeners.end())
		m_listeners.erase(it);
}

void Toggle::setState(bool isOn) {
	m_isOn = isOn;
}

bool Toggle::getState() {
	return m_isOn;
}