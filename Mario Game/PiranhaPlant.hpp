#pragma once
#include "Block.hpp"
#include "Mario.hpp"
#include "Collision.hpp"
#include "TextureManager.hpp"
#include "ParticleSystem.hpp"
#include "Random.hpp"
#include "Item.hpp"
#include "GameManager.hpp"
#include "Enemy.hpp"
#include "AutoControl.hpp"
#include "SoundComponent.hpp"

class PiranhaPlant : public Enemy
{
private:
    AutoControl& m_autoControl;
    SoundComponent& m_sound;
    bool m_isDead;
    bool m_isActive; // Trạng thái có đang hoạt động hay không
    float m_timer; // Bộ đếm thời gian cho trạng thái chờ
    float m_positionOffset; // Độ cao hiện tại của cây
    bool m_isRising; // Cờ để kiểm tra cây đang trồi lên hay xuống

public:
    PiranhaPlant(Object* parent = nullptr);
    void onCollisionEnter(Collision& col, const Direction& side) override;
    void hit(bool isDestroy);
    void update();
};