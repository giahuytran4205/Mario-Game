#pragma once

#include "Slider.hpp"
#include <SFML/Audio.hpp>
#include "SoundComponent.hpp"
#include "SoundBufferManager.hpp"

template<SoundTrack track>
class MusicSlider : public Slider<float>
{
private:
    SoundComponent& m_soundComponent;

public:
    MusicSlider(RenderWindow& window, const float& minVal, const float& maxVal, const float& val = 0, const Vector2f& pos = { 0, 0 }, Object* parent = nullptr)
        : Slider<float>(window, minVal, maxVal, val, pos, parent), m_soundComponent(addComponent<SoundComponent>())
    {
        if (val > maxVal)
            throw std::out_of_range("Default volume can't be greater than max volume");
        m_soundComponent.play(track);
        m_soundComponent.setVolume(val);
    }

    void update() override
    {
        Slider<float>::update();
        m_soundComponent.setVolume(Slider<float>::getCurrentValue());
    }
};


