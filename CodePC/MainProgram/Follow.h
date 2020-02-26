#pragma once
#include "Commands.h"
class Follow :
	public Commands
{
	// Inherited via Commands
	virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;
};

