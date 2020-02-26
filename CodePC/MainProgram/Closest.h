#pragma once
#include "Commands.h"
class Closest :
	public Commands
{
	// Inherited via Commands
private:


public:
	Closest();
	virtual ~Closest();
	virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;
};

