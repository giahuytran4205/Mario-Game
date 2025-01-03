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
	
	Object& operator=(const Object& obj);

	bool isActive() const override;
	bool isDestroyed() const override;
	bool isPause() const override;
	void update() override;
	void render() override;
	Object* getParent() const;
	void setParent(Object* parent);
	Transform2D& getTransform2D();
	void setEnable(bool enable);
	void destroy();
};