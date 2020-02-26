#pragma once
#include "Commands.h"
class AttackProphet :
	public Commands
{
	// Inherited via Commands
	virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;
};

