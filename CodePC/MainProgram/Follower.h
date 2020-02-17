#pragma once
#include "GameEntity.h"
class Follower :
	public GameEntity
{
private:
	int damage;
	int soulValue;
	float attackRange;
	bool alive;
public:
	void increaseDamageDone(int increase);
};

