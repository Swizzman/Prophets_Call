#pragma once
#include "GameEntity.h"
#include <iostream>
class Commands
{

private:


public:
	virtual GameEntity* calculateRoute(GameEntity *thisObject, GameEntity ** object ) = 0;

};

