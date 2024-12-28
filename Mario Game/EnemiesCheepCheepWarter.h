#pragma once
#include "EnemiesCheepCheepBase.h"

class EnemiesCheepCheepWarter : public EnemiesCheepCheepBase
{
public:
	EnemiesCheepCheepWarter(Mario& mario, Object* parent);
	void update();
};

