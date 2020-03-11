#pragma once
#include "Commands.h"

class AttackProphet :
	public Commands
{
	// Inherited via Commands
public:
	AttackProphet();
	virtual ~AttackProphet();
	//virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
};

