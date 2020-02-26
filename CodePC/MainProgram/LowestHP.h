#pragma once
#include "Commands.h"
class LowestHP :
	public Commands
{
	// Inherited via Commands
public:
	LowestHP();
	virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;
};

