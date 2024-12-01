#pragma once

#include "Slider.hpp"
#include "VolumeSlider.hpp"
#include <SFML/Audio.hpp>
#include "SoundComponent.hpp"
#include "SoundBufferManager.hpp"

class TotalVolumeSlider : public Slider<float>
{
public:
    TotalVolumeSlider(RenderWindow& window, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr, SoundComponent& soundComponent)
        : Slider<float>(window, 0.0f, 100.0f, 50.0f, pos, parent)
    {
        SoundComponent::setTotalVolume(Slider<float>::getCurrentValue());
    }

    void update() override
    {
        Slider<float>::update();
        SoundComponent::setTotalVolume(Slider<float>::getCurrentValue());
    }
};

