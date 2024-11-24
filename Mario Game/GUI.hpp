#pragma once
#include "Common.hpp"
#include "SFML/Graphics.hpp"
#include "Object.hpp"
#include "SpriteRenderer.hpp"
#include "Rect.hpp"
#include "EventSystem.hpp"
using namespace sf;

class GUI : public Object, public IEventListener {
protected:
	SpriteRenderer& m_background;
	RenderWindow* m_window;
	bool m_isSelected;
	bool m_isPressed;
	bool m_isHovered;
	bool m_isOnDrag;
	bool m_isInteractable;

public:
	GUI();
	GUI(const FRect& rect, RenderWindow* window, Object* parent = nullptr);
	GUI(float left, float top, float width, float height, RenderWindow* window, Object* parent = nullptr);
	~GUI();

	void update() override;
	void render() override;
	void handleEvent(const Event& event) override;
	virtual void onSelected();
	virtual void onDeselect();
	virtual void onPressed();
	virtual void onHovered();
	virtual void onUnhovered();
	virtual void onClick();
	virtual void onKeyPressed(const Keyboard::Key& key);
	virtual void onDrag(const Vector2f& mousePos);
	bool isSelected();
	bool isPressed();
	bool isHovered();
	bool isOnDrag();
	bool isInteractable();
	void setSelect(bool isSelect);
	void setInteractable(bool isInteractable);
};