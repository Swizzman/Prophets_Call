#pragma once
#include "Commands.h"


class AttackProphet :
	public Commands
{
public:
	AttackProphet();
	virtual ~AttackProphet();

	// Inherited via Commands
	virtual sf::Vector2f calculateRoute(GameEntity* thisObject, GameEntity* enemyObject, Follower* object) override;
};

