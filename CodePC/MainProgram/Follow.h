#pragma once
#include "Commands.h"
class Follow :
	public Commands
{
	// Inherited via Commands
public:
	
	Follow();
	virtual ~Follow();
	//sf::Vector2f calculateVectorRoute(GameEntity* thisObject , GameEntity* enemyObject, GameEntity* object);
	//virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, GameEntity* object) override;
};

