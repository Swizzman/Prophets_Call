#pragma once
#include "Commands.h"
class Prophet;
class LowestHP :
	public Commands
{
private:
	float range;
	bool attackProphetBool;
public:
	LowestHP();
	virtual ~LowestHP();

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
};

