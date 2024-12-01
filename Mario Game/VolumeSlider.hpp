#pragma once

#include "Slider.hpp"
#include <SFML/Audio.hpp>
#include "SoundComponent.hpp"
#include "SoundBufferManager.hpp"

template<SoundTrack track>
class VolumeSlider : public Slider<float>
{
private:
    SoundComponent& m_soundComponent;

public:
    VolumeSlider(RenderWindow& window, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr, SoundComponent& soundComponent)
        : Slider<float>(window, 0.0f, 100.0f, 50.0f, pos, parent), m_soundComponent(soundComponent)
    {
        if (val > maxVal)
            throw std::out_of_range("Default volume can't be greater than max volume");
        m_soundComponent.setVolume(val);
    }

    void update() override
    {
        Slider<float>::update();
        m_soundComponent.setVolume(Slider<float>::getCurrentValue());
    }
};


