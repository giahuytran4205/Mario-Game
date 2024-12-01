#pragma once

#include "GameManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "InputField.hpp"
#include "TextView.hpp"
#include "Enum.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "SFML/Graphics.hpp"

class MainScene : public Scene
{
private:
	
public:
	MainScene();
	~MainScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};