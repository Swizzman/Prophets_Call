#pragma once
#include "Commands.h"

class Prophet;
class Closest :
	public Commands
{
	// Inherited via Commands
private:
	bool attackProphetBool;

public:
	Closest();
	virtual ~Closest();

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
	//virtual GameEntity* calculateRoute(GameEntity* thisObject, GameEntity** object) override;
};

