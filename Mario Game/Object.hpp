#pragma once
#include "Common.hpp"
#include "ECS.hpp"
#include "SpriteRenderer.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Object : public Entity {
protected:
	Object* m_parent = nullptr;
	Transform2D& m_transform;
	SpriteRenderer& m_sprite;

public:
	Object(Object* parent = nullptr);
	Object(const Object& obj);
	virtual ~Object();
	virtual Object* clone();
	
	bool isActive();
	Object* getParent();
	void setParent(Object* parent);
	Transform2D& getTransform2D();
	void setRenderOrder(int order);
	void setTexture(Texture& texture);
	void loadTexture(string filename);
	void update() override;
	void destroy();
	void render() override;
};