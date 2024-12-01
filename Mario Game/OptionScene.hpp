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
#include "MusicSlider.hpp"
#include "Toggle.hpp"
#include "SFML/Graphics.hpp"

class TextView;
class Button;
class InputField;
template<SoundTrack track>
class MusicSlider;

class OptionScene : public Scene
{
private:
	MusicSlider<SoundTrack::BACKGROUND>* m_themeMusicSlider;

public:
	OptionScene();
	~OptionScene();

	void update() override;
	void render() override;
	void handleEvent(const sf::Event& event) override;
};

