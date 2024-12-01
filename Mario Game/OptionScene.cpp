#include "OptionScene.hpp"

OptionScene::OptionScene()
{
	sf::RenderWindow& window = GameManager::getInstance()->getRenderWindow();
	sf::View& view = GameManager::getInstance()->getView();

	// SET VIEW;
	view.reset(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(FloatRect(0, 0, 1, 1));
	window.setView(view);

	// SLIDER
	m_themeMusicSlider = new VolumeSlider<SoundTrack::BACKGROUND>(
		window,
		0.0f, 200.0f,
		0.0f,
		sf::Vector2f(static_cast<float>(window.getSize().x) / 2.0f, static_cast<float>(window.getSize().y) / 2.0f),
		this
	);
}

OptionScene::~OptionScene()
{
	delete m_themeMusicSlider;
}

void OptionScene::update()
{
}

void OptionScene::render()
{
}

void OptionScene::handleEvent(const sf::Event& event)
{
}
