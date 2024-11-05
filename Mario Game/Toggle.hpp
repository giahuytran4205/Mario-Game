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
	vector<void (*)(bool isOn)> m_listeners;

public:
	Toggle(RenderWindow& window, Texture& onTexture, Texture& offTexture, void (*action) (bool isOn) = nullptr, Object* parent = nullptr);
	~Toggle();

	void onClick() override;
	void setOnTexture(Texture& texture);
	void setOffTexture(Texture& texture);
	void onTrigger();
	void addListener(void (*func) (bool isOn));
	void removeListener(void (*func) (bool isOn));
	void setState(bool isOn);
	bool getState();
};