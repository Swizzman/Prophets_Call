#pragma once
#include "GameEntity.h"
#include <iostream>

class Follower;
class Commands
{

private:


public:
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) = 0;
	//virtual GameEntity* calculateRoute(GameEntity *thisObject, GameEntity ** object ) = 0;

};

