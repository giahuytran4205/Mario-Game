#pragma once
#include "Common.hpp"

class Controller : public Component {
private:

public:
	Controller();
	~Controller();

	void init() override;
	void update() override;
	void lateUpdate() override;

};