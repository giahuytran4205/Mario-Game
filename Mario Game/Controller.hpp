#pragma once
#include "ECS.hpp"

class Controller : Component {
private:

public:
	void init() override;
	void update() override;
	void lateUpdate() override;

};