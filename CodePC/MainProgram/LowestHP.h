#pragma once
#include "Commands.h"
class Prophet;
class LowestHP :
	public Commands
{
private:
	float range = 700;
	bool attackProphetBool;
	bool enemysNotInRange;
	sf::Vector2f tempDist;
	float magniTemp = 100000;
	float health = 100000;
	
	sf::Vector2f thisEnemy;

	int whichGroup;
	int whichFollower;
public:
	LowestHP();
	virtual ~LowestHP();

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
};

