#pragma once
#include "Commands.h"
class Prophet;
class LowestHP :
	public Commands
{
	// Inherited via Commands
private:
	float range = 1000;
	bool attackProphetBool;
public:
	LowestHP();
	virtual ~LowestHP();
	//virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
};

