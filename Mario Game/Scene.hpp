#pragma once
#include "ECS.hpp"
#include "Object.hpp"
#include "EventSystem.hpp"
#include <iostream>

class Scene : public Object, public IEventListener {
public:
	Scene() {}
	~Scene() {}
	void update() override {}
	void render() override {}
	void handleEvent(const Event& event) override {}
};