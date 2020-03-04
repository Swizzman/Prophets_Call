#pragma once
#include "GameEntity.h"
#include <iostream>


class Commands
{

private:


public:
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object) = 0;
	//virtual GameEntity* calculateRoute(GameEntity *thisObject, GameEntity ** object ) = 0;

};

