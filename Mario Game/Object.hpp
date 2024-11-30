#pragma once
#include "Common.hpp"
#include "ECS.hpp"
#include "SFML/Graphics.hpp"
using namespace sf;

class Object : public Entity {
protected:
	Object* m_parent = nullptr;
	Transform2D& m_transform;

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
	void update() override;
	void render() override;
	void setEnable(bool enable);
	void destroy();
};