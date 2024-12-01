#pragma once

#include "GameManager.hpp"
#include "Scene.hpp"
#include "Button.hpp"
#include "InputField.hpp"
#include "TextView.hpp"
#include "Enum.hpp"
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "SoundBufferManager.hpp"
#include "SoundComponent.hpp"
#include "VolumeSlider.hpp"
#include "TotalVolumeSlider.hpp"
#include "Toggle.hpp"
#include "SFML/Graphics.hpp"

class TextView;
class Button;
class InputField;
template<SoundTrack track>
class VolumeSlider;
class TotalVolumeSlider;

class OptionScene : public Scene
{
private:

public:
	OptionScene();
	~OptionScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

