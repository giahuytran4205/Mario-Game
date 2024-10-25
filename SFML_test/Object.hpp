#pragma once
#include "ECS.hpp"
#include "Transform2D.hpp"
using namespace std;

class Object : public Entity {
protected:
	Object* m_parent;
	bool m_active;
	int m_renderLayer;
	Transform2D& m_transform = addComponent<Transform2D>();
	Sprite m_sprite;
	Texture m_texture;

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