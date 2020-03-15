#pragma once
#include "GameEntity.h"

class Follower;
class Commands
{

private:


public:
	Commands();
	virtual ~Commands();
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) = 0;
	//virtual GameEntity* calculateRoute(GameEntity *thisObject, GameEntity ** object ) = 0;

};

