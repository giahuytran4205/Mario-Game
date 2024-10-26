#pragma once
#include "Common.hpp"
#include "ECS.hpp"
#include "SpriteRenderer.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Object : public Entity {
protected:
	Object* m_parent;
	bool m_active;
	int m_renderLayer;
	Transform2D& m_transform;
	SpriteRenderer& m_sprite;

public:
	Object(Object* parent = nullptr);
	virtual ~Object();
	
	bool isActive();
	Object* getParent();
	void setParent(Object* parent);
	Transform2D& getTransform2D();
	void setRenderLayer(int layer);
	void setTexture(Texture& texture);
	void loadTexture(string filename);
	void destroy();
	void render() override;
};