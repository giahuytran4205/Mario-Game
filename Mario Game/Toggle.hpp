#pragma once
#include "Common.hpp"
#include "GUI.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Toggle : public GUI {
private:
	Texture m_onTexture;
	Texture m_offTexture;
	bool m_isOn;
	void (*m_action) (bool isOn);

public:
	Toggle(RenderWindow& window, Texture& onTexture, Texture& offTexture, void (*action) (bool isOn) = nullptr, Object* parent = nullptr);
	~Toggle();

	void onClick() override;
	void setOnTexture(Texture& texture);
	void setOffTexture(Texture& texture);
	void onTrigger();
	void setAction(void (*func) (bool isOn));
	void setState(bool isOn);
	bool getState();
};