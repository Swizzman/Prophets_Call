#pragma once
#include "GameEntity.h"
class Commands
{

private:

public:
	virtual GameEntity* calculateRoute(GameEntity *thisObject, GameEntity ** object ) = 0;

};

