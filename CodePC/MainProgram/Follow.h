#pragma once
#include "Commands.h"
class Prophet;
class Follow :
	public Commands
{
	// Inherited via Commands
private:

	bool attackProphetBool;
public:
	
	Follow();
	virtual ~Follow();
	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
};

