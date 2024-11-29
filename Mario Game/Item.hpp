#ifndef ITEM_HPP
#define ITEM_HPP
#include "Block.hpp"
#include "TileSet.hpp"
#include <vector>
#include "Physics2D.hpp"

enum ItemType {
    OneUpMushroom,  // Green mushroom - extra life
    KoopaShell,     // Turtle shell
    BuzyShell,      // Spiny shell  
    MagicMushroom,  // Red mushroom - makes Mario big
    FireFlower,     // Fire power flower
    Starman,        // Star - invincibility
    Coin            // Standard coin
};

class Item : public Block {
private:
    ItemType m_type;
    bool m_isPlayAnim;
    float m_elapsedTime;
    int m_index;
    vector<Frame> m_anim;
    bool m_active;
    Color m_debugColor;

public:
    Item(Object* parent = nullptr);
    Item(ItemType type, Object* parent = nullptr);
    Item(float x, float y, float width = 16, float height = 16, ItemType type = ItemType::MagicMushroom);
    ~Item();

    void setAnim(vector<Frame>& anim);
    void update() override;
    void render() override;
    void onCollisionEnter(Collision& col) override;
    ItemType getType() const { return m_type; }
    void setActive(bool active) { m_active = active; }
    bool isActive() const { return m_active; }
    void setPosition(const Vector2f& pos);
};

#endif